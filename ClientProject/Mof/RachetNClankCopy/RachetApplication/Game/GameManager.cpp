#include "GameManager.h"

#include "My/Core/Trait.h"
#include "My/Core/Utility.h"

#include "../Stage/StageDefine.h"
#include "../Factory/FactoryManager.h"
#include "GameSystem/Save/SaveData.h"
#include "GameSystem/Save/SaveSystem.h"
#include "../Actor/Character/Enemy.h"
#include "../Actor/Character/Player.h"
#include "../Factory/ActorBuilder.h"


void my::GameManager::AddElement(const std::shared_ptr<my::Actor>& ptr) {
    _game_world.AddActor(ptr);
    _renderer.AddElement(ptr);
    _physic_world.AddActor(ptr);
}

void my::GameManager::RemoveElement(const std::shared_ptr<my::Actor>& ptr) {
    _game_world.RemoveActor(ptr);
    _renderer.RemoveElement(ptr);
    _physic_world.RemoveActor(ptr);
}

my::GameManager::GameManager() :
    _resource(),
    _ui_canvas(),
    _game_world(),
    _renderer(),
    _game_money(),
    _weapon_system(),
    _quick_change(),
    _stage() {

}

my::GameManager::~GameManager() {
}

void my::GameManager::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
    if (type == "AddRequest") {
        ptr->AddObserver(shared_from_this());
        _created_actors.push_back(ptr);
    } // if
    if (type == "DeleteRequest") {
        _delete_actors.push_back(ptr);
    } // if
}

void my::GameManager::SetResourceManager(const std::shared_ptr<my::ResourceMgr>& ptr) {
    this->_resource = ptr;
}

void my::GameManager::SetUICanvas(const std::shared_ptr<my::UICanvas>& ptr) {
    this->_ui_canvas = ptr;
}

bool my::GameManager::Initialize(void) {
    _weapon_system = std::make_shared<my::WeaponSystem>();
    _game_money = std::make_unique<my::GameMoney>();
    _quick_change = std::make_shared<my::QuickChangeSystem>();
    _game_money->SetResourceManager(_resource);
    _quick_change->SetResourceManager(_resource);
    _quick_change->SetUICanvas(_ui_canvas);
    // game system
    auto save_data = my::SaveData();
    my::SaveSystem().Fetch(save_data);
    _game_money->Initialize(save_data.GetMoney());
    _weapon_system->Initialize(save_data, shared_from_this());
    _quick_change->Initialize({}, _weapon_system);


    // stage
    if (!_stage.Load("../Resource/test.json")) {
        return false;
    } // if
    _stage.Initialize();

    auto param = new my::Actor::Param();
    // chara
    for (auto enemy_spawn : _stage.GetEnemySpawnArray()) {
        _ASSERT_EXPR(enemy_spawn.second->GetType() == StageObjectType::StageObjectType_EnemySpawnPoint, L"Œ^‚ªˆê’v‚µ‚Ü‚¹‚ñ");
        auto builder = enemy_spawn.first.c_str();
        param->name = enemy_spawn.second->GetName();
        param->transform.position = enemy_spawn.second->GetPosition();
        auto enemy = my::FactoryManager::Singleton().CreateActor<my::Enemy>(builder, param);
        enemy->AddObserver(shared_from_this());
        this->AddElement(enemy);
    } // for
    param->transform.position = Mof::CVector3(0.0f, 3.0f, 0.0f);
    auto player = my::FactoryManager::Singleton().CreateActor<Player>("../Resource/builder/player.json", param);
    player->AddObserver(shared_from_this());
    this->AddElement(player);
    _weapon_system->AddMechanicalWeaponObserver(player);
    _quick_change->AddWeaponObserver(_weapon_system);

    ut::SafeDelete(param);
    return true;
}

bool my::GameManager::Input(void) {
    _game_money->Input();
    _quick_change->Input();
    _game_world.Input();

    return true;
}

bool my::GameManager::Update(float delta_time) {
    for (auto& ptr : _created_actors) {
        this->AddElement(ptr);
    } // for
    _created_actors.clear();
    for (auto& ptr : _delete_actors) {
        this->RemoveElement(ptr);
    } // for
    _delete_actors.clear();

    // update
    _quick_change->Update();
    _stage.Update();


    _game_world.Update(delta_time);

    _physic_world.Update();
    _physic_world.CollisionStage(&_stage);


    ::ImGui::Begin("GameManager");
    ::ImGui::Text(" ");
    ::ImGui::End();
    return true;
}

bool my::GameManager::Render(void) {
    _renderer.Render();
    _stage.Render();
    _quick_change->Render();
    _game_money->Render();
    return true;
}

bool my::GameManager::Release(void) {
    _stage.Release();

    //! save
    std::vector<std::string> weapon;
    _weapon_system->CreateAvailableMechanicalWeaponNames(weapon);
    auto save_param = my::SaveDataParam(_game_money->GetValue(), weapon);
    my::SaveSystem().Save(save_param);

    _quick_change->Release();
    return true;
}