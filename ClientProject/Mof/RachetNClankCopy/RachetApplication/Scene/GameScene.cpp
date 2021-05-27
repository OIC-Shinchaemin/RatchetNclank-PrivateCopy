#include "GameScene.h"

#include "../Factory/FactoryManager.h"
#include "../Actor/Character/Enemy.h"
#include "../Actor/Character/Player.h"
#include "../Actor//Terrain/Terrain.h"
#include "../Component/CameraComponent.h"


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
        _subject.Notify(my::SceneMessage(my::SceneType::kClearScene, ""));
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_SPACE)) {
        _bridge_event->AllDelete();
    } // if
#endif // _DEBUG
    _stage_view_event->Update(delta_time);
    _bridge_event->Update(delta_time);
    _ship_event->Update(delta_time);
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

    
    // update
    _stage.Update(delta_time);
    _game_world.Update(delta_time);

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
    _ui_canvas(),
    _game(),
    _bridge_event(std::make_shared<my::BridgeEvent>()),
    _ship_event(std::make_shared<my::ShipEvent>()),
    _stage_view_event(std::make_shared<my::StageViewEvent>()) {
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
        _subject.Notify(my::SceneMessage(my::SceneType::kClearScene, ""));
    } // if
}

void my::GameScene::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

void my::GameScene::SetGameManager(std::weak_ptr<my::GameManager> ptr) {
    this->_game = ptr;
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
    if (!_stage.Load("../Resource/stage/stage.json")) {
        return false;
    } // if

    if (auto game = _game.lock()) {
        game->GameSystemLoad();
    } // if
    super::LoadComplete();

    _ship_event->GetShipEventSubject().AddObserver(shared_from_this());
    _bridge_event->AddObserver(_ship_event);
    return true;
}

#include "../Stage/Gimmick/Bridge.h"
bool my::GameScene::Initialize(void) {
    _stage.Initialize();
    _bridge_event->SetStage(&_stage);
    _bridge_event->Initialize();
    _ship_event->Initialize();
    _stage_view_event->Initialize();
    _bridge_event->AddObserver(_ship_event);

    for (auto gimmick : _stage.GetGimmickArray()) {
        auto temp = std::dynamic_pointer_cast<Bridge>(gimmick);
        if (temp) {
            temp->AddObserver(_ship_event);
        } // if
    } // for
    

    auto param = new my::Actor::Param();
    // enemy
    for (auto enemy_spawn : _stage.GetEnemySpawnArray()) {
        auto event_sphere = Mof::CSphere(180.0f, -30.0f, 25.0f, 40.0f);
        _ASSERT_EXPR(enemy_spawn.second->GetType() == StageObjectType::EnemySpawnPoint, L"型が一致しません");
        auto builder = enemy_spawn.first.c_str();
        param->name = enemy_spawn.second->GetName();
        param->transform.position = enemy_spawn.second->GetPosition();
        auto enemy = my::FactoryManager::Singleton().CreateActor<my::Enemy>(builder, param);
        this->AddElement(enemy);

        if (event_sphere.CollisionPoint(param->transform.position)) {
            _bridge_event->AddTriggerActor(enemy);
        } // if
    } // for
    // player
    param->transform.position = Mof::CVector3(5.0f, 5.0f, -5.0f);
    param->transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi, 0.0f);
    auto player = my::FactoryManager::Singleton().CreateActor<my::Player>("../Resource/builder/player.json", param);
    this->AddElement(player);
    _stage_view_event->GetSubject()->AddObserver(player->GetComponent<my::CameraComponent>());
    _ship_event->SetCameraComponent(player->GetComponent<my::CameraComponent>());


    // game system
    if (auto game = _game.lock()) {
        auto weapon_system = game->GetWeaponSystem();
        auto quick_change = game->GetQuickChange();
        // game system
        game->GetHelpDesk()->Initialize();
        weapon_system->Initialize(shared_from_this());
        quick_change->Initialize(weapon_system);

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
    _stage.Release();
    if (auto game = _game.lock()) {
        game->GameSystemRelease();
    } // if
    return true;
}