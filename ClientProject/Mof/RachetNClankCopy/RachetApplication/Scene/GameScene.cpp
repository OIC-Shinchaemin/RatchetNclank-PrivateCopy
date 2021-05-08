#include "GameScene.h"


#include "My/Core/Trait.h"
#include "My/Core/Utility.h"

#include "../Stage/StageDefine.h"
#include "../Factory/FactoryManager.h"
#include "../Actor/Character/Enemy.h"
#include "../Actor/Character/Player.h"
#include "../Actor//Ship/Ship.h"
#include "../Factory/ActorBuilder.h"


void my::GameScene::AddElement(const std::shared_ptr<my::Actor>& ptr) {
    // add
    ptr->AddObserver(shared_from_this());
    _game_world.AddActor(ptr);
    _renderer.AddElement(ptr);
    _physic_world.AddActor(ptr);
}

void my::GameScene::RemoveElement(const std::shared_ptr<my::Actor>& ptr) {
    if (ptr->GetTag() == "Enemy") {
        ut::SwapPopback(_for_bridge_event_actors, ptr);
        if (_for_bridge_event_actors.empty()) {
            for (auto gimmick : _stage.GetGimmickArray()) {
                if (gimmick->GetType() == StageObjectType::Bridge) {
                    gimmick->ActionStart();
                    _bridge_event_subject.Notify("GimmickAction", nullptr);
                } // if
            } // for
        } // if
    } // if
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

    if (::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
        _subject.Notify(my::SceneMessage(my::SceneType::kClearScene, ""));
    } // if

    for (auto& ptr : _created_actors) {
        this->AddElement(ptr);
    } // for
    _created_actors.clear();
    for (auto& ptr : _delete_actors) {
        this->RemoveElement(ptr);
    } // for
    _delete_actors.clear();

    if (_re_initialize) {
        this->ReInitialize();
    } // if

    // update
    _stage.Update(delta_time);
    _game_world.Update(delta_time);

    // collision
    _physic_world.Update();
    _physic_world.CollisionStage(&_stage);
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
    float delta_time = ::CUtilities::GetFPS();
    //::CGraphicsUtilities::RenderString(20.0f, 20.0f, "FPS = %f", delta_time);
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
    _simple_light(),
    _ui_canvas(),
    _game(),
    _for_bridge_event_actors(),
    _bridge_event_subject() {
}

my::GameScene::~GameScene() {
}

void my::GameScene::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
    if (type == "AddRequest") {
        ptr->AddObserver(shared_from_this());
        _created_actors.push_back(ptr);
    } // if
    if (type == "DeleteRequest") {
        _delete_actors.push_back(ptr);
    } // if
    if (type == "PlayerDead") {
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
    if (!_stage.Load("../Resource/stage/test.json")) {
        return false;
    } // if
    super::LoadComplete();
    return true;
}

bool my::GameScene::Initialize(void) {
    // light
    _simple_light.SetDirection(-math::vec3::kOne);
    _simple_light.SetDiffuse(def::color_rgba::kWhite);
    _simple_light.SetAmbient(def::color_rgba::kWhite * 0.8f);
    ::CGraphicsUtilities::SetDirectionalLight(&_simple_light);

    _stage.Initialize();

    auto param = new my::Actor::Param();
    // chara
    _for_bridge_event_actors.clear();
    _for_bridge_event_actors.reserve(_stage.GetEnemySpawnArray().size());
    for (auto enemy_spawn : _stage.GetEnemySpawnArray()) {
        auto event_sphere = Mof::CSphere(180.0f, -30.0f, 25.0f, 40.0f);
        _ASSERT_EXPR(enemy_spawn.second->GetType() == StageObjectType::EnemySpawnPoint, L"Œ^‚ªˆê’v‚µ‚Ü‚¹‚ñ");
        auto builder = enemy_spawn.first.c_str();
        param->name = enemy_spawn.second->GetName();
        param->transform.position = enemy_spawn.second->GetPosition();
        auto enemy = my::FactoryManager::Singleton().CreateActor<my::Enemy>(builder, param);
        this->AddElement(enemy);

        if (event_sphere.CollisionPoint(param->transform.position)) {
            _for_bridge_event_actors.push_back(enemy);
        } // if
    } // for


    param->transform.position = Mof::CVector3(5.0f, 5.0f, -5.0f);
    param->transform.rotate = Mof::CVector3(0.0f, -math::kHalfPi * 0.7f, 0.0f);
    auto player = my::FactoryManager::Singleton().CreateActor<Player>("../Resource/builder/player.json", param);
    this->AddElement(player);

    param->transform.position = Mof::CVector3(10.0f, -4.0f, -25.0f);
    param->name = "ship";
    auto ship = my::FactoryManager::Singleton().CreateActor<my::Ship>("../Resource/builder/ship.json", param);
    this->AddElement(ship);
    _bridge_event_subject.AddObserver(ship);
    player->AddObserver(ship);


    // game system
    if (auto game = _game.lock()) {
        auto weapon_system = game->GetWeaponSystem();
        auto quick_change = game->GetQuickChange();

        weapon_system->Initialize(shared_from_this());
        quick_change->Initialize({}, game->GetWeaponSystem());
        weapon_system->AddMechanicalWeaponObserver(player);
        quick_change->AddWeaponObserver(weapon_system);
    } // if

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