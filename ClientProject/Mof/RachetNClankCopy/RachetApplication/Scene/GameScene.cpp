#include "GameScene.h"


#include "My/Core/Trait.h"
#include "My/Core/Utility.h"

#include "../Stage/StageDefine.h"
#include "../Factory/FactoryManager.h"
#include "../Game/GameSystem/Save/SaveData.h"
#include "../Game/GameSystem/Save/SaveSystem.h"
#include "../Actor/Character/Enemy.h"
#include "../Actor/Character/Player.h"
#include "../Actor//Ship/Ship.h"
#include "../Factory/ActorBuilder.h"


void my::GameScene::AddElement(const std::shared_ptr<my::Actor>& ptr) {
    ptr->AddObserver(shared_from_this());
    _game_world.AddActor(ptr);
    _renderer.AddElement(ptr);
    _physic_world.AddActor(ptr);
}

void my::GameScene::RemoveElement(const std::shared_ptr<my::Actor>& ptr) {
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

bool my::GameScene::SceneRender(void) {
    ::g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    ::g_pGraphics->SetDepthEnable(true);
    
    int fps = ::CUtilities::GetFPS();
    ::CGraphicsUtilities::RenderString(50.0f, 500.0f, "FPS = %d", fps);
    
    _renderer.Render();
    _stage.Render();
    _game_money->Render();
    return true;
}

my::GameScene::GameScene() :
    _created_actors(),
    _delete_actors(),
    _game_world(),
    _renderer(),
    _physic_world(),
    _game_money(),
    _weapon_system(),
    _quick_change(),
    _stage(),
    _re_initialize(false),
    _simple_light(),
    _resource(),
    _ui_canvas() {
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

    if (type == "ShipCollision") {
        _subject.Notify(my::SceneMessage(my::SceneType::kClearScene, ""));
    } // if
}

void my::GameScene::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::GameScene::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

std::string my::GameScene::GetName(void) {
    return my::SceneType::kGameScene;
}

bool my::GameScene::Load(std::shared_ptr<my::Scene::Param> param) {
    super::Load(param);
    _weapon_system = std::make_shared<my::WeaponSystem>();
    _game_money = std::make_unique<my::GameMoney>();
    _quick_change = std::make_shared<my::QuickChangeSystem>();

    _game_money->SetResourceManager(_resource);
    _weapon_system->SetResourceManager(_resource);
    _weapon_system->SetUICanvas(_ui_canvas);
    _quick_change->SetResourceManager(_resource);
    _quick_change->SetUICanvas(_ui_canvas);

    // stage
    if (!_stage.Load("../Resource/stage/test.json")) {
        return false;
    } // if
    return true;
}

bool my::GameScene::Initialize(void) {
    // light
    _simple_light.SetDirection(-math::vec3::kOne);
    _simple_light.SetDiffuse(def::color_rgba::kWhite);
    _simple_light.SetAmbient(def::color_rgba::kWhite * 0.8f);
    ::CGraphicsUtilities::SetDirectionalLight(&_simple_light);

    // game system
    auto save_data = my::SaveData();
    my::SaveSystem().Fetch(save_data);
    _game_money->Initialize(save_data.GetMoney());
    _weapon_system->Initialize(save_data, shared_from_this());
    _quick_change->Initialize({}, _weapon_system);
    _stage.Initialize();


    auto param = new my::Actor::Param();
    // chara
    for (auto enemy_spawn : _stage.GetEnemySpawnArray()) {

        _ASSERT_EXPR(enemy_spawn.second->GetType() == StageObjectType::EnemySpawnPoint, L"Œ^‚ªˆê’v‚µ‚Ü‚¹‚ñ");
        auto builder = enemy_spawn.first.c_str();
        param->name = enemy_spawn.second->GetName();
        param->transform.position = enemy_spawn.second->GetPosition();
        auto enemy = my::FactoryManager::Singleton().CreateActor<my::Enemy>(builder, param);
        this->AddElement(enemy);
    } // for

    param->transform.position = Mof::CVector3(5.0f, 5.0f, -5.0f);
    param->transform.rotate = Mof::CVector3(0.0f, - math::kHalfPi * 0.7f, 0.0f);
    auto player = my::FactoryManager::Singleton().CreateActor<Player>("../Resource/builder/player.json", param);
    player->Generate(_resource.lock());
    this->AddElement(player);

    param->transform.position = Mof::CVector3(2.0f, 1.0f, 5.0f);
    auto ship = my::FactoryManager::Singleton().CreateActor<my::Ship>("../Resource/builder/ship.json", param);
    this->AddElement(ship);



    _weapon_system->AddMechanicalWeaponObserver(player);
    _quick_change->AddWeaponObserver(_weapon_system);

    ut::SafeDelete(param);
    _re_initialize = false;
    return true;
}

bool my::GameScene::Input(void) {
    _game_world.Input();
    return true;
}

bool my::GameScene::Update(float delta_time) {
    super::Update(delta_time);

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
    _quick_change->Update();
    _stage.Update(delta_time);
    _game_world.Update(delta_time);

    // collision
    _physic_world.Update();
    _physic_world.CollisionStage(&_stage);
    return true;
}

bool my::GameScene::Release(void) {
    //! save
    std::vector<std::string> weapon;
    _weapon_system->CreateAvailableMechanicalWeaponNames(weapon);
    auto save_param = my::SaveDataParam(_game_money->GetValue(), weapon);
    my::SaveSystem().Save(save_param);
    _quick_change->Release();
    _stage.Release();
    return true;
}