#include "GameSceneInitializer.h"

#include "../Gamepad.h"
#include "../Factory/FactoryManager.h"
#include "../Actor/Character/Enemy.h"
#include "../Actor/Character/Player.h"
#include "../Actor/Character/King.h"
#include "../Actor/Character/Queen.h"
#include "../Actor/Character/Scarecrow.h"
#include "../Actor/Facility/Shop.h"
#include "../Actor/Facility/Barrack.h"
#include "../Actor//Terrain/Terrain.h"
#include "../Actor/Gimmick/Wall.h"
#include "../Actor/Gimmick/Fence.h"
#include "../Component/CameraComponent.h"
#include "../Component/HPComponent.h"
#include "../Component/SightRecognitionComponent.h"
#include "../Stage/Gimmick/Bridge.h"
#include "../Stage/Gimmick/Elevator.h"
#include "../Event/BridgeEvent.h"
#include "../Event/ShipEvent.h"
#include "../Event/StageViewEvent.h"
#include "../Event/TextSystemStartEvent.h"
#include "../Stage/Gimmick/Bridge.h"
#include "../Game/Audio/AudioUtility.h"


ratchet::scene::GameSceneInitializer::GameSceneInitializer() {
}

bool ratchet::scene::GameSceneInitializer::AddPlayer(std::shared_ptr<ratchet::game::GameManager> game, std::shared_ptr<ratchet::event::EventManager> event, std::shared_ptr<ratchet::scene::GameScene> out) {
    std::vector<std::shared_ptr<Elevator>> elevators;
    for (auto gimmick : out->_stage.GetGimmickArray()) {
        auto temp_elevator = std::dynamic_pointer_cast<Elevator>(gimmick);
        if (temp_elevator) {
            elevators.push_back(temp_elevator);
        } // if
    } // for
    std::shared_ptr<ratchet::event::StageViewEvent> stage_view_event = event->GetEvent<ratchet::event::StageViewEvent>();


    auto param = ratchet::actor::Actor::Param();

    // player
    param.name = "player";
    param.tag = "Player";


    if (!out->_player_dead) {
        Mof::CVector3 init_position = Mof::CVector3(5.0f, 5.0f, -5.0f);
        param.transform.position = init_position;
    } // if
    else {
        Mof::CVector3 revival_position = Mof::CVector3(55.0, -25.0f, 25.0f);
        param.transform.position = revival_position;
    } // else


    param.transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
    auto player = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::character::Player>("../Resource/builder/player.json", &param);
    ratchet::event::EventReferenceTable::Singleton().Register(player->GetName(), player);
    out->AddElement(player);
    out->_text_system->GetTextSystemClosedMessageSubject()->AddObserver(player);

    if (stage_view_event) {
        stage_view_event->GetCameraObservable()->AddObserver(player->GetComponent<ratchet::component::CameraComponent>());
    } // if
    else {
        auto hp = player->GetComponent<ratchet::component::HpComponent>();
        hp->RegisterUI();
        auto camera = player->GetComponent<ratchet::component::CameraComponent>()->GetCameraController()->GetService();
        camera->RegisterGlobalCamera();
        camera->SetAzimuth(camera->GetDefaultAzimuth());
        camera->SetAltitude(camera->GetDefaultAltitude());
    } // else


    player->SetEffectContainer(out->_effect);
    player->GetCharacterDamageApplyMessageSubject()->AddObserver(out);
    player->GetComponent<component::SightRecognitionComponent>()->GetContactEnemyMessageSubject()->AddObserver(out);
    for (auto elevator : elevators) {
        elevator->GetElevatorArrivalMessageSubject()->AddObserver(player);
    } // for
    {
        param.name = "weapon";
        param.tag = "OmniWrench";
        auto omniwrench = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::weapon::OmniWrench>("builder/omni_wrench.json", &param);
        player->AddChild(omniwrench);
        out->AddElement(omniwrench);
    }


        // game system
    {
        auto weapon_system = game->GetWeaponSystem();
        auto quick_change = game->GetQuickChange();
        auto help_desk = game->GetHelpDesk();
        auto user_action_helper = game->GetUserActionHelper();

        user_action_helper->SetResourceManager(out->_resource);
        user_action_helper->SetUICanvas(out->_ui_canvas);
        user_action_helper->RegisterUI();
        player->GetCharacterTalkableMessageSubject()->AddObserver(user_action_helper);

        player->GetShopSystemSubject()->AddObserver(game->GetShopSystem());
        player->GetQuickChangeSubject()->AddObserver(game->GetQuickChange());
        player->PushNotificationableSubject("QuickChange");
        out->_text_system->GetTextSystemClosedMessageSubject()->AddObserver(player);

        weapon_system->AddMechanicalWeaponObserver(player);
        quick_change->AddInfoObserver(player);
        auto weapons = weapon_system->GetWeaponMap();
        for (auto& pair : weapons) {
            player->AddChild(pair.second);
        } // for
    } // if
    return true;
}

bool ratchet::scene::GameSceneInitializer::Execute(std::shared_ptr<ratchet::game::GameManager>& game, std::shared_ptr<ratchet::event::EventManager>& event, std::shared_ptr<ratchet::scene::GameScene>& out) {
    out->_stage.Initialize();
    ratchet::event::EventReferenceTable::Singleton().Reset();

    if (auto game = out->_game.lock()) {
        ratchet::event::EventReferenceTable::Singleton().Register("GameManager", game);
    } // if
    if (auto e = out->_event.lock()) {
        ratchet::event::EventReferenceTable::Singleton().Register("EventManager", e);
    } // if
    if (auto light = out->_light_manager.lock()) {
        ratchet::event::EventReferenceTable::Singleton().Register("LightManager", light);
    } // if


    ratchet::event::EventReferenceTable::Singleton().Register("Stage", &out->_stage);
    ratchet::event::EventReferenceTable::Singleton().Register("TextSystem", out->_text_system);

    if (auto r = out->_resource.lock()) {
        auto se_player = out->GetSEPlayer();
        auto add_cound = game::audio::SEAddSound(se_player, r);
        add_cound.Add(ratchet::game::audio::SEType::SystemSelect, "../Resource/se/system_select.mp3");
        add_cound.Add(ratchet::game::audio::SEType::SystemEner, "../Resource/se/system_enter.mp3");
        add_cound.Add(ratchet::game::audio::SEType::SystemMenuOpen, "../Resource/se/system_menu_open.mp3");
        add_cound.Add(ratchet::game::audio::SEType::EnemyDamage, "../Resource/se/enemy_damage.mp3");
        add_cound.Add(ratchet::game::audio::SEType::EnemyDead, "../Resource/se/enemy_dead.mp3");

    } // if

    std::shared_ptr<ratchet::event::ShipEvent> ship_event;
    std::shared_ptr<ratchet::event::StageViewEvent> stage_view_event;
    auto shared_this = out;

    out->_text_system->GetTextSystemClosedMessageSubject()->Clear();
    //out->_text_system->GetTextSystemOpenMessageSubject()->Clear();
    //out->_text_system->SetScene(out);
    //out->_text_system->GetTextSystemOpenMessageSubject()->AddObserver(out); 
    out->_text_system->GetTextSystemClosedMessageSubject()->AddObserver(out);

    if (auto e = event) {
        e->InitializeGameEvent();
        ship_event = e->CreateGameEvent<ratchet::event::ShipEvent>();
        ship_event->ShipEventEndMessageSubject()->AddObserver(out);
        stage_view_event = e->CreateGameEvent<ratchet::event::StageViewEvent>();
        stage_view_event->SetGameScene(shared_this);
        stage_view_event->SetTextSystem(out->_text_system);
        stage_view_event->GetStageViewEventMessageSubject()->AddObserver(shared_this);
    } // if

    ship_event->Initialize();
    stage_view_event->Initialize();
    ship_event->GetShipEventSubject()->AddObserver(out);

    std::vector<std::shared_ptr<Elevator>> elevators;
    for (auto gimmick : out->_stage.GetGimmickArray()) {
        auto temp = std::dynamic_pointer_cast<Bridge>(gimmick);
        if (temp) {
            temp->AddObserver(ship_event);
        } // if
        auto temp_elevator = std::dynamic_pointer_cast<Elevator>(gimmick);
        if (temp_elevator) {
            temp_elevator->SetEventManager(event);
            ratchet::event::EventReferenceTable::Singleton().Register(temp_elevator->GetName(),
                                                                      temp_elevator);
            elevators.push_back(temp_elevator);
        } // if
    } // for

    //return true;

    auto param = new ratchet::actor::Actor::Param();

    this->AddPlayer(game, event, out);



    {
        param->transform.position = Mof::CVector3(15.0f, -5.0f, 7.0f);
        param->transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
        auto shop = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::facility::Shop >("../Resource/builder/shop.json", param);
        out->AddElement(shop);
    }




    // game system
    {
        auto pause_system = game->GetGamePauseSystem();
        auto weapon_system = game->GetWeaponSystem();
        auto quick_change = game->GetQuickChange();
        auto help_desk = game->GetHelpDesk();
        auto game_money = game->GetGameMoney();
        auto shop_system = game->GetShopSystem();

        shop_system->GetInfoSubject()->AddObserver(shared_this);
        help_desk->RegisterQuest(ratchet::game::gamesystem::GameQuest(ratchet::game::gamesystem::GameQuest::Type::EnemyDestroy));

        game_money->SetEventManager(out->_event.lock());
        game_money->GetTextSystemMessageSubject()->AddObserver(out->_text_system);
        game_money->SetTextSystem(out->_text_system);
        game_money->SetGameScene(out);
        // game system
        weapon_system->Initialize(shared_this);
        quick_change->Initialize(weapon_system);
        game_money->Initialize();
        help_desk->Initialize();
        shop_system->Initialize();
        pause_system->Initialize();

        auto quest = ratchet::game::gamesystem::GameQuest(ratchet::game::gamesystem::GameQuest::Type::ToFront);
        quick_change->AddWeaponObserver(weapon_system);
        out->_pause_menu_subject.AddObserver(pause_system);
    } // if


    auto help_desk = game->GetHelpDesk();
    // enemy
    for (auto enemy_spawn : out->_stage.GetEnemySpawnArray()) {
        auto event_sphere = Mof::CSphere(180.0f, -30.0f, 25.0f, 40.0f);
        _ASSERT_EXPR(enemy_spawn.second->GetType() == StageObjectType::EnemySpawnPoint, L"Œ^‚ªˆê’v‚µ‚Ü‚¹‚ñ");
        auto builder = enemy_spawn.first.c_str();
        param->name = enemy_spawn.second->GetName();
        param->transform.position = enemy_spawn.second->GetPosition();
        auto enemy = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::character::Enemy>(builder, param);
        out->AddElement(enemy);
        enemy->SetEffectContainer(out->_effect);
        enemy->GetCharacterDamageApplyMessageSubject()->AddObserver(out);
    } // for

    {
        rapidjson::Document document;
        if (!ut::ParseJsonDocument("stage/placement_data.json", document)) {
            return false;
        } // if

        auto& elem_list = document["element_list"];
        std::string file_path = std::string("../Resource/builder/");
        for (int i = 0, n = elem_list.Size(); i < n; i++) {
            auto& elem_data = elem_list[i];
            std::string type = elem_data["type"].GetString();
            std::string builder_path = elem_data["builder_path"].GetString();
            auto& paramater = elem_data["paramater"];
            std::string name = paramater["name"].GetString();
            std::string tag = paramater["tag"].GetString();
            auto& transform = elem_data["transform"];
            auto pos = transform["position"].GetArray();
            auto rot = transform["rotation"].GetArray();
            auto sca = transform["scale"].GetArray();

            param->name = name;
            param->tag = tag;
            for (int j = 0, m = pos.Size(); j < m; j++) {
                param->transform.position[j] = pos[j].GetFloat();
            } // for
            for (int j = 0, m = rot.Size(); j < m; j++) {
                param->transform.rotate[j] = rot[j].GetFloat();
            } // for
            for (int j = 0, m = sca.Size(); j < m; j++) {
                param->transform.scale[j] = sca[j].GetFloat();
            } // for
            if (type == "Barrack") {
                auto elem = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::facility::Barrack>((file_path + builder_path).c_str(), param);
                out->AddElement(elem);
            } // if
            // other actor create...
            else if (type == "OtherBarrack") {
            } // else if
        } // for
    }




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

    {

        // wall
        def::Transform wall_transforms[]{
            def::Transform(Mof::CVector3(43.0f, -4.0f, -13.0f)),
            def::Transform(Mof::CVector3(-3.0f, -4.0f, -51.0f)),
        };
        param->tag = "wall";
        param->name = "wall_1";
        for (auto& transform : wall_transforms) {
            param->transform.position = transform.position;
            param->transform.scale = transform.scale;
            auto wall = ratchet::factory::FactoryManager::Singleton().CreateActor < ratchet::actor::gimmick::Wall >("../Resource/builder/wall.json", param);
            out->AddElement(wall);
            ratchet::event::EventReferenceTable::Singleton().Register(param->name, wall);
            param->name = "wall_2";
        } // for
    }


    {
        // fence
        def::Transform wall_transforms[]{
            def::Transform(Mof::CVector3(-10.0f, -5.0f, 5.0f), Mof::CVector3(0.0f, math::ToRadian(180.0f),0.0f)),
            def::Transform(Mof::CVector3(-15.0f, -5.0f, 5.0f), Mof::CVector3(0.0f, math::ToRadian(180.0f),0.0f)),
            def::Transform(Mof::CVector3(-20.0f, -5.0f, 5.0f), Mof::CVector3(0.0f, math::ToRadian(180.0f),0.0f)),
            def::Transform(Mof::CVector3(-25.0f, -5.0f, 5.0f), Mof::CVector3(0.0f, math::ToRadian(180.0f),0.0f)),
            def::Transform(Mof::CVector3(-10.0f, -5.0f, -20.0f), Mof::CVector3(0.0f, math::ToRadian(180.0f),0.0f)),
            def::Transform(Mof::CVector3(-15.0f, -5.0f, -20.0f), Mof::CVector3(0.0f, math::ToRadian(180.0f),0.0f)),
            def::Transform(Mof::CVector3(-20.0f, -5.0f, -20.0f), Mof::CVector3(0.0f, math::ToRadian(180.0f),0.0f)),
            def::Transform(Mof::CVector3(-25.0f, -5.0f, -20.0f), Mof::CVector3(0.0f, math::ToRadian(180.0f),0.0f)),

            def::Transform(Mof::CVector3(-5.0f, -5.0f, -20.0f), Mof::CVector3(0.0f, math::ToRadian(90.0f),0.0f)),
            def::Transform(Mof::CVector3(-5.0f, -5.0f,  0.0f), Mof::CVector3(0.0f, math::ToRadian(90.0f),0.0f)),
        };
        param->tag = "fence";
        param->name = "fence";
        int index = 0;
        for (auto& transform : wall_transforms) {
            param->transform.position = transform.position;
            param->transform.rotate = transform.rotate;
            param->transform.scale = transform.scale;
            auto fence = ratchet::factory::FactoryManager::Singleton().CreateActor < ratchet::actor::gimmick::Fence>("../Resource/builder/fence.json", param);
            out->AddElement(fence);
            param->name = std::string("fence") + std::to_string(index);
            index++;
        } // for
    }
    // npc
    {
        def::Transform npc_transforms[]{
            def::Transform(Mof::CVector3(8.0f, -5.0f, -2.0f), Mof::CVector3(0.0f, 45.0f , 0.0f)),
        };
        param->tag = "king";
        param->name = "king";
        for (auto& transform : npc_transforms) {
            param->transform.position = transform.position;
            param->transform.rotate = transform.rotate;
            param->transform.scale = transform.scale;
            auto king = ratchet::factory::FactoryManager::Singleton().CreateActor < ratchet::actor::character::King >("../Resource/builder/king.json", param);
            auto tex = out->GetResource()->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/ui/icon/question.png");
            king->SetHelpDesk(help_desk);
            king->SetTexture(tex);
            king->SetGameScene(out);
            king->GetTextSystemMessageSubject()->AddObserver(out->_text_system);
            king->SetEffectContainer(out->_effect);
            out->AddElement(king);
        } // for
    }

    ut::SafeDelete(param);
    return true;
}