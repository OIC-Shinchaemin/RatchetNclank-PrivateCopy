#include "GameScene.h"

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
#include "../Event/EventReferenceTable.h"


void ratchet::scene::GameScene::AddElement(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    // add
    ptr->AddObserver(shared_from_this());
    _game_world.AddActor(ptr);
    _renderer.AddElement(ptr);
    _physic_world.AddActor(ptr);
}

void ratchet::scene::GameScene::RemoveElement(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    // remove
    _game_world.RemoveActor(ptr);
    _renderer.RemoveElement(ptr);
    _physic_world.RemoveActor(ptr);
}

void ratchet::scene::GameScene::ReInitialize(void) {
    _renderer.Reset();
    _game_world.Reset();
    _physic_world.Reset();
    this->Initialize();
}

bool ratchet::scene::GameScene::SceneUpdate(float delta_time) {
    super::SceneUpdate(delta_time);
    
    if (_re_initialize) {
        this->ReInitialize();
    } // if

    for (auto& ptr : _created_actors) {
        this->AddElement(ptr);
    } // for
    _created_actors.clear();
    for (auto& ptr : _delete_actors) {
        this->RemoveElement(ptr);
    } // for
    _delete_actors.clear();


    if (_state != super::State::Pause) {
        // input
        _game_world.Input();

        // update
        _stage.Update(delta_time);
        _game_world.Update(delta_time);
    } // if
    // collision
    _physic_world.CollisionStage(&_stage);
    _physic_world.Update();
    return true;
}

bool ratchet::scene::GameScene::LoadingUpdate(float delta_time) {
    return false;
}

bool ratchet::scene::GameScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(true);

    _renderer.Render();
    _stage.Render();

    ::g_pGraphics->SetDepthEnable(false);
    return true;
}

bool ratchet::scene::GameScene::LoadingRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);
    ::CGraphicsUtilities::RenderString(10.0f, 10.0f, "Now Loading");
    return true;
}

ratchet::scene::GameScene::GameScene() :
    _created_actors(),
    _delete_actors(),
    _game_world(),
    _renderer(),
    _physic_world(),
    _stage(),
    _re_initialize(false),
    _game(),
    _event() {
}

ratchet::scene::GameScene::~GameScene() {
}

void ratchet::scene::GameScene::OnNotify(const char* type, const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    if (type == "AddRequest") {
        ptr->AddObserver(shared_from_this());
        _created_actors.push_back(ptr);
    } // if
    if (type == "DeleteRequest") {
        ptr->RemoveObserver(shared_from_this());
        _delete_actors.push_back(ptr);
    } // if
    if (type == "PlayerDead") {
        // retry
        _re_initialize = true;
    } // if
    if (type == "GameClear") {
        _subject.Notify(scene::SceneMessage(ratchet::scene::SceneType::kClearScene, ""));
    } // if
}

void ratchet::scene::GameScene::OnNotify(const ratchet::game::gamesystem::ShopSystem::Info& info) {
    if (info.close) {
        this->_state = super::State::Active;
    } // if
    else {
        this->_state = super::State::Pause;
    } // else
}

void ratchet::scene::GameScene::SetGameManager(std::weak_ptr<ratchet::game::GameManager> ptr) {
    this->_game = ptr;
}

void ratchet::scene::GameScene::SetEventManager(std::weak_ptr<ratchet::event::EventManager> ptr) {
    this->_event = ptr;
}

std::string ratchet::scene::GameScene::GetName(void) {
    return ratchet::scene::SceneType::kGameScene;
}

bool ratchet::scene::GameScene::Load(std::shared_ptr<ratchet::scene::Scene::Param> param) {
    super::Load(param);
    if (auto r = _resource.lock()) {
        r->Load(param->resource.c_str());
    } // if
    // stage
    if (!_stage.Load("../Resource/stage/stage.json")) {
        return false;
    } // if

    if (auto game = _game.lock()) {
        game->GameSystemLoad();
    } // if
    super::LoadComplete();

    return true;
}

bool ratchet::scene::GameScene::Initialize(void) {
    _stage.Initialize();
    ratchet::event::EventReferenceTable::Singleton().Reset();

    std::shared_ptr<ratchet::event::BridgeEvent> bridge_event;
    std::shared_ptr<ratchet::event::ShipEvent> ship_event;
    std::shared_ptr<ratchet::event::StageViewEvent> stage_view_event;
    if (auto e = _event.lock()) {
        e->InitializeGameEvent();
        bridge_event = e->CreateGameEvent<ratchet::event::BridgeEvent>();
        ship_event = e->CreateGameEvent<ratchet::event::ShipEvent>();
        stage_view_event = e->CreateGameEvent<ratchet::event::StageViewEvent>();
    } // if

    bridge_event->SetStage(&_stage);
    bridge_event->Initialize();
    ship_event->Initialize();
    stage_view_event->Initialize();

    bridge_event->GetCameraSubject()->AddObserver(ship_event);
    ship_event->GetShipEventSubject()->AddObserver(shared_from_this());

    for (auto gimmick : _stage.GetGimmickArray()) {
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
    this->AddElement(player);
    stage_view_event->GetCameraObservable()->AddObserver(player->GetComponent<ratchet::component::CameraComponent>());

    {
        param->transform.position = Mof::CVector3(15.0f, -5.0f, 7.0f);
        param->transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
        auto shop = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::facility::Shop >("../Resource/builder/shop.json", param);
        this->AddElement(shop);
    }
    {
        param->name = "weapon";
        param->tag = "OmniWrench";
        auto omniwrench = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::weapon::OmniWrench>("builder/omni_wrench.json", param);
        player->AddChild(omniwrench);
        this->AddElement(omniwrench);
    }


    // game system
    if (auto game = _game.lock()) {
        auto pause_system = game->GetGamePauseSystem();
        auto weapon_system = game->GetWeaponSystem();
        auto quick_change = game->GetQuickChange();
        auto help_desk = game->GetHelpDesk();
        auto game_money = game->GetGameMoney();
        auto shop_system = game->GetShopSystem();


        shop_system->GetInfoSubject()->AddObserver(std::dynamic_pointer_cast<this_type>(shared_from_this()));
        player->GetShopSystemSubject()->AddObserver(game->GetShopSystem());
        player->GetQuickChangeSubject()->AddObserver(game->GetQuickChange());
        player->PushNotificationableSubject("QuickChange");
        player->GetQuestSubject()->AddObserver(help_desk);

        // game system
        weapon_system->Initialize(shared_from_this());
        quick_change->Initialize(weapon_system);
        game_money->Initialize();
        help_desk->Initialize();
        shop_system->Initialize();
        pause_system->Initialize();

        auto quest = ratchet::game::gamesystem::GameQuest(ratchet::game::gamesystem::GameQuest::Type::ToFront);
        help_desk->OnNotify(quest);
        bridge_event->GetQuestSubject()->AddObserver(help_desk);
        weapon_system->AddMechanicalWeaponObserver(player);
        quick_change->AddWeaponObserver(weapon_system);
        quick_change->AddInfoObserver(player);
        _pause_menu_subject.AddObserver(pause_system);

        auto weapons = weapon_system->GetWeaponMap();
        for (auto& pair : weapons) {
            player->AddChild(pair.second);
        } // for


        auto item0 = std::make_shared<ratchet::game::gamesystem::GamePauseSystemItem>([&]() {
            _subject.Notify(scene::SceneMessage(ratchet::scene::SceneType::kTitleScene, ""));
            return true;
        });
        item0->SetText("タイトルに戻る");

        auto item1 = std::make_shared<ratchet::game::gamesystem::GamePauseSystemItem>([&]() {
            _subject.Notify(scene::SceneMessage(ratchet::scene::SceneType::kGameScene, ""));
            return true;
        });
        item1->SetText("リトライ");

        auto item2 = std::make_shared<ratchet::game::gamesystem::GamePauseSystemItem>([&]() {
            _game.lock()->GetGamePauseSystem()->Inactive();
            this->_state = super::State::Active;
            return true;
        });
        item2->SetText("もどる");

        pause_system->AddItem(item0);
        pause_system->AddItem(item1);
        pause_system->AddItem(item2);
    } // if


    auto help_desk = _game.lock()->GetHelpDesk();
    // enemy
    for (auto enemy_spawn : _stage.GetEnemySpawnArray()) {
        auto event_sphere = Mof::CSphere(180.0f, -30.0f, 25.0f, 40.0f);
        _ASSERT_EXPR(enemy_spawn.second->GetType() == StageObjectType::EnemySpawnPoint, L"型が一致しません");
        auto builder = enemy_spawn.first.c_str();
        param->name = enemy_spawn.second->GetName();
        param->transform.position = enemy_spawn.second->GetPosition();
        auto enemy = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::character::Enemy>(builder, param);
        this->AddElement(enemy);
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
        this->AddElement(terrain);
    } // for


    ut::SafeDelete(param);
    _re_initialize = false;
    return true;
}

bool ratchet::scene::GameScene::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_RETURN) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_BACK)) {
        if (auto game = _game.lock()) {
            if (!game->GetGamePauseSystem()->IsActive()) {
                if (!_event.lock()->GetEvent<ratchet::event::StageViewEvent>()) {
                    if (this->_state != super::State::Pause) {
                        this->_state = super::State::Pause;
                        _pause_menu_subject.Notify(true);
                    } // if
                } // if
            } // if
        } // if
    } // if
    return true;
}

bool ratchet::scene::GameScene::Release(void) {
    super::Release();
    _stage.Release();
    if (auto game = _game.lock()) {
        game->GetGamePauseSystem()->Clear();
        _pause_menu_subject.Clear();
        game->GameSystemRelease();
    } // if
    return true;
}