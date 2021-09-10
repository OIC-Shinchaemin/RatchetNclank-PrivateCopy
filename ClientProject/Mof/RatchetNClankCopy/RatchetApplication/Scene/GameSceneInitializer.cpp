#include "GameSceneInitializer.h"

#include "../Gamepad.h"
#include "../Factory/FactoryManager.h"
#include "../Actor/Character/Enemy.h"
#include "../Actor/Character/Player.h"
#include "../Actor/Facility/Shop.h"
#include "../Actor//Terrain/Terrain.h"
#include "../Component/CameraComponent.h"
#include "../Stage/Gimmick/Bridge.h"
#include "../Event/BridgeEvent.h"
#include "../Event/ShipEvent.h"
#include "../Event/StageViewEvent.h"
#include "../Event/TextSystemStartEvent.h"
#include "../Stage/Gimmick/Bridge.h"


ratchet::scene::GameSceneInitializer::GameSceneInitializer() {
}
bool ratchet::scene::GameSceneInitializer::Execute(std::shared_ptr<ratchet::game::GameManager>& game, std::shared_ptr<ratchet::event::EventManager>& event, std::shared_ptr<ratchet::scene::GameScene>& out) {
    out->_stage.Initialize();
    ratchet::event::EventReferenceTable::Singleton().Reset();

    std::shared_ptr<ratchet::event::BridgeEvent> bridge_event;
    std::shared_ptr<ratchet::event::ShipEvent> ship_event;
    std::shared_ptr<ratchet::event::StageViewEvent> stage_view_event;
    auto shared_this = out;// std::dynamic_pointer_cast<scene::GameScene>(shared_from_this());

    if (auto e = event) {
        e->InitializeGameEvent();
        bridge_event = e->CreateGameEvent<ratchet::event::BridgeEvent>();
        ship_event = e->CreateGameEvent<ratchet::event::ShipEvent>();
        stage_view_event = e->CreateGameEvent<ratchet::event::StageViewEvent>();
        stage_view_event->SetGameScene(shared_this);
        stage_view_event->SetTextSystem(out->_text_system);
        stage_view_event->GetStageViewEventMessageSubject()->AddObserver(shared_this);
    } // if

    bridge_event->SetStage(&out->_stage);
    bridge_event->Initialize();
    ship_event->Initialize();
    stage_view_event->Initialize();

    bridge_event->GetCameraSubject()->AddObserver(ship_event);
    ship_event->GetShipEventSubject()->AddObserver(out);

    for (auto gimmick : out->_stage.GetGimmickArray()) {
        auto temp = std::dynamic_pointer_cast<Bridge>(gimmick);
        if (temp) {
            temp->AddObserver(ship_event);
        } // if
    } // for


    auto param = new ratchet::actor::Actor::Param();

    // player
    param->transform.position = Mof::CVector3(5.0f, 5.0f, -5.0f);
    param->transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
    auto player = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::character::Player>("../Resource/builder/player.json", param);
    out->AddElement(player);
    stage_view_event->GetCameraObservable()->AddObserver(player->GetComponent<ratchet::component::CameraComponent>());

    {
        param->transform.position = Mof::CVector3(15.0f, -5.0f, 7.0f);
        param->transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
        auto shop = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::facility::Shop >("../Resource/builder/shop.json", param);
        out->AddElement(shop);
    }
    {
        param->name = "weapon";
        param->tag = "OmniWrench";
        auto omniwrench = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::weapon::OmniWrench>("builder/omni_wrench.json", param);
        player->AddChild(omniwrench);
        out->AddElement(omniwrench);
    }


    // game system
    //if (auto game = _game.lock()) 
    {
        auto pause_system = game->GetGamePauseSystem();
        auto weapon_system = game->GetWeaponSystem();
        auto quick_change = game->GetQuickChange();
        auto help_desk = game->GetHelpDesk();
        auto game_money = game->GetGameMoney();
        auto shop_system = game->GetShopSystem();

//        shop_system->GetInfoSubject()->AddObserver(std::dynamic_pointer_cast<this_type>(shared_from_this()));
        shop_system->GetInfoSubject()->AddObserver(shared_this);
        player->GetShopSystemSubject()->AddObserver(game->GetShopSystem());
        player->GetQuickChangeSubject()->AddObserver(game->GetQuickChange());
        player->PushNotificationableSubject("QuickChange");
        player->GetQuestSubject()->AddObserver(help_desk);

        // game system
        weapon_system->Initialize(shared_this);
        quick_change->Initialize(weapon_system);
        game_money->Initialize();
        help_desk->Initialize();
        shop_system->Initialize();
        pause_system->Initialize();

        auto quest = ratchet::game::gamesystem::GameQuest(ratchet::game::gamesystem::GameQuest::Type::ToFront);
        help_desk->OnNotify(quest);
        stage_view_event->SetHelpDesk(help_desk);
        bridge_event->GetQuestSubject()->AddObserver(help_desk);
        weapon_system->AddMechanicalWeaponObserver(player);
        quick_change->AddWeaponObserver(weapon_system);
        quick_change->AddInfoObserver(player);
        out->_pause_menu_subject.AddObserver(pause_system);

        auto weapons = weapon_system->GetWeaponMap();
        for (auto& pair : weapons) {
            player->AddChild(pair.second);
        } // for

        
        auto item0 = std::make_shared<ratchet::game::gamesystem::GamePauseSystemItem>([&]() {
            out->_subject.Notify(scene::SceneMessage(ratchet::scene::SceneType::kTitleScene, ""));
            return true;
        });
        item0->SetText("タイトルに戻る");

        auto item1 = std::make_shared<ratchet::game::gamesystem::GamePauseSystemItem>([&]() {
            out->_subject.Notify(scene::SceneMessage(ratchet::scene::SceneType::kGameScene, ""));
            return true;
        });
        item1->SetText("リトライ");

        auto item2 = std::make_shared<ratchet::game::gamesystem::GamePauseSystemItem>([&]() {
            game->GetGamePauseSystem()->Inactive();
            shared_this->SetState(scene::Scene::State::Active);
            return true;
        });
        item2->SetText("もどる");

        pause_system->AddItem(item0);
        pause_system->AddItem(item1);
        pause_system->AddItem(item2);
    } // if


    auto help_desk = game->GetHelpDesk();
    // enemy
    for (auto enemy_spawn : out->_stage.GetEnemySpawnArray()) {
        auto event_sphere = Mof::CSphere(180.0f, -30.0f, 25.0f, 40.0f);
        _ASSERT_EXPR(enemy_spawn.second->GetType() == StageObjectType::EnemySpawnPoint, L"型が一致しません");
        auto builder = enemy_spawn.first.c_str();
        param->name = enemy_spawn.second->GetName();
        param->transform.position = enemy_spawn.second->GetPosition();
        auto enemy = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::character::Enemy>(builder, param);
        out->AddElement(enemy);
        enemy->GetQuestSubject()->AddObserver(help_desk);

        if (event_sphere.CollisionPoint(param->transform.position)) {
            bridge_event->AddTriggerActor(enemy);
        } // if
    } // for

    // terrain
    def::Transform terrain_transforms[]{
        def::Transform(Mof::CVector3(0.0f, -31.2f, 0.0f), Mof::CVector3(), Mof::CVector3(540.0f, 1.0f, 540.0f)),
    };
    for (auto& transform : terrain_transforms) {
        param->transform.scale = transform.scale;
        param->transform.position = transform.position;
        auto terrain = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::terrain::Terrain>("../Resource/builder/water_flow.json", param);
        out->AddElement(terrain);
    } // for
    ut::SafeDelete(param);


    return true;
}