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


void my::GameScene::AddElement(const std::shared_ptr<my::Actor>& ptr) {
    // add
    ptr->AddObserver(shared_from_this());
    _game_world.AddActor(ptr);
    _renderer.AddElement(ptr);
    _physic_world.AddActor(ptr);
}

void my::GameScene::RemoveElement(const std::shared_ptr<my::Actor>& ptr) {
    // remove
    _game_world.RemoveActor(ptr);
    _renderer.RemoveElement(ptr);
    _physic_world.RemoveActor(ptr);
}

void my::GameScene::ReInitialize(void) {
    _renderer.Reset();
    _game_world.Reset();
    _physic_world.Reset();
    this->Initialize();
}

bool my::GameScene::SceneUpdate(float delta_time) {
    super::SceneUpdate(delta_time);
#ifdef _DEBUG
    if (::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        _subject.Notify(scene::SceneMessage(my::SceneType::kClearScene, ""));
    } // if
#endif // _DEBUG

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

bool my::GameScene::LoadingUpdate(float delta_time) {
    return false;
}

bool my::GameScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(true);

    _renderer.Render();
    _stage.Render();

    ::g_pGraphics->SetDepthEnable(false);
    return true;
}

bool my::GameScene::LoadingRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(false);
    ::CGraphicsUtilities::RenderString(10.0f, 10.0f, "Now Loading");
    return true;
}

my::GameScene::GameScene() :
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

my::GameScene::~GameScene() {
}

void my::GameScene::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
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
        _subject.Notify(scene::SceneMessage(my::SceneType::kClearScene, ""));
    } // if
}

void my::GameScene::OnNotify(const my::ShopSystem::Info& info) {
    if (info.close) {
        this->_state = super::State::Active;
    } // if
    else {
        this->_state = super::State::Pause;
    } // else
}

void my::GameScene::SetGameManager(std::weak_ptr<my::GameManager> ptr) {
    this->_game = ptr;
}

void my::GameScene::SetEventManager(std::weak_ptr<my::EventManager> ptr) {
    this->_event = ptr;
}

std::string my::GameScene::GetName(void) {
    return my::SceneType::kGameScene;
}

bool my::GameScene::Load(std::shared_ptr<my::Scene::Param> param) {
    super::Load(param);
    if (auto r = _resource.lock()) {
        r->Load(param->resource.c_str());
    } // if
    // stage
    //if (!_stage.Load("../Resource/stage/stage.json")) {
    if (!_stage.Load("../Resource/stage/test.json")) {
        return false;
    } // if

    if (auto game = _game.lock()) {
        game->GameSystemLoad();
    } // if
    super::LoadComplete();

    return true;
}

bool my::GameScene::Initialize(void) {
    _stage.Initialize();
    my::EventReferenceTable::Singleton().Reset();

    std::shared_ptr<my::BridgeEvent> bridge_event;
    std::shared_ptr<my::ShipEvent> ship_event;
    std::shared_ptr<my::StageViewEvent> stage_view_event;
    if (auto e = _event.lock()) {
        e->InitializeGameEvent();
        bridge_event = e->CreateGameEvent<my::BridgeEvent>();
        ship_event = e->CreateGameEvent<my::ShipEvent>();
        stage_view_event = e->CreateGameEvent<my::StageViewEvent>();
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


    auto param = new my::Actor::Param();
    // enemy
    for (auto enemy_spawn : _stage.GetEnemySpawnArray()) {
        auto event_sphere = Mof::CSphere(180.0f, -30.0f, 25.0f, 40.0f);
        _ASSERT_EXPR(enemy_spawn.second->GetType() == StageObjectType::EnemySpawnPoint, L"Œ^‚ªˆê’v‚µ‚Ü‚¹‚ñ");
        auto builder = enemy_spawn.first.c_str();
        param->name = enemy_spawn.second->GetName();
        param->transform.position = enemy_spawn.second->GetPosition();
        auto enemy = my::FactoryManager::Singleton().CreateActor<my::Enemy>(builder, param);
        this->AddElement(enemy);

        if (event_sphere.CollisionPoint(param->transform.position)) {
            bridge_event->AddTriggerActor(enemy);
        } // if
    } // for
    // player
    param->transform.position = Mof::CVector3(5.0f, 5.0f, -5.0f);
    param->transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
    auto player = my::FactoryManager::Singleton().CreateActor<my::Player>("../Resource/builder/player.json", param);
    this->AddElement(player);
    stage_view_event->GetCameraObservable()->AddObserver(player->GetComponent<my::CameraComponent>());

    {
        param->transform.position = Mof::CVector3(15.0f, -5.0f, 7.0f);
        param->transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
        auto shop = my::FactoryManager::Singleton().CreateActor<my::Shop >("../Resource/builder/shop.json", param);
        this->AddElement(shop);
    }
    {
        param->name = "weapon";
        param->tag = "OmniWrench";
        auto omniwrench = my::FactoryManager::Singleton().CreateActor<my::OmniWrench>("builder/omni_wrench.json", param);
        player->AddChild(omniwrench);
        this->AddElement(omniwrench);
    }


    // game system
    if (auto game = _game.lock()) {
        auto weapon_system = game->GetWeaponSystem();
        auto quick_change = game->GetQuickChange();
        auto help_desk = game->GetHelpDesk();
        auto game_money = game->GetGameMoney();
        auto shop_system = game->GetShopSystem();

        shop_system->GetInfoSubject()->AddObserver(std::dynamic_pointer_cast<this_type>(shared_from_this()));
        player->GetShopSystemSubject()->AddObserver(game->GetShopSystem());
        player->GetQuickChangeSubject()->AddObserver(game->GetQuickChange());
        player->PushNotificationableSubject("QuickChange");
        // game system
        weapon_system->Initialize(shared_from_this());
        quick_change->Initialize(weapon_system);
        game_money->Initialize();
        help_desk->Initialize();
        shop_system->Initialize();
        auto quest = my::GameQuest(my::GameQuest::Type::EnemyDestroy);
        help_desk->OnNotify(quest);
        bridge_event->GetQuestSubject()->AddObserver(help_desk);
        weapon_system->AddMechanicalWeaponObserver(player);
        quick_change->AddWeaponObserver(weapon_system);
        quick_change->AddInfoObserver(player);

        auto weapons = weapon_system->GetWeaponMap();
        for (auto& pair : weapons) {
            player->AddChild(pair.second);
        } // for
    } // if

    // terrain
    def::Transform terrain_transforms[]{
        def::Transform(Mof::CVector3(0.0f, -31.2f, 0.0f), Mof::CVector3(), Mof::CVector3(540.0f, 1.0f, 540.0f)),
    };
    for (auto& transform : terrain_transforms) {
        param->transform.scale = transform.scale;
        param->transform.position = transform.position;
        auto terrain = my::FactoryManager::Singleton().CreateActor<my::Terrain>("../Resource/builder/water_flow.json", param);
        this->AddElement(terrain);
    } // for



    ut::SafeDelete(param);
    _re_initialize = false;
    return true;
}

bool my::GameScene::Release(void) {
    super::Release();
    _stage.Release();
    if (auto game = _game.lock()) {
        //_shop_system_subject.RemoveObserver(game->GetShopSystem());
        //_quick_change_subject.RemoveObserver(game->GetQuickChange());


        game->GameSystemRelease();
    } // if
    return true;
}