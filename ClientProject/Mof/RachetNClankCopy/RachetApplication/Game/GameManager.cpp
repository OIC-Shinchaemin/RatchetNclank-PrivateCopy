#include "GameManager.h"

#include "My/Core/Trait.h"
#include "My/Core/Utility.h"
#include "../GameSystem/Save/SaveData.h"
#include "../GameSystem/Save/SaveSystem.h"
#include "../Character/Enemy.h"
#include "../Character/Player.h"


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

void my::GameManager::Collision(void) {
    _physic_world.Update();
}

my::GameManager::GameManager() :
    _game_world(),
    _renderer(),
    _game_money(),
    _weapon_system(),
    _quick_change(),
    _stage(),
    _character() {

}

my::GameManager::~GameManager() {
}

void my::GameManager::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
    if (type == "DeleteRequest") {
        _delete_actors.push_back(ptr);
    } // if
}

bool my::GameManager::Initialize(void) {
    _stage.Initialize();

    _game_money = std::make_unique<my::GameMoney>();
    _weapon_system = std::make_shared<my::WeaponSystem>();
    _quick_change = std::make_shared<my::QuickChangeSystem>();
    auto player = std::make_shared<Player>();
    _character = player;
    _weapon_system->AddWeaponObserver(player);
    _quick_change->AddWeaponObserver(_weapon_system);

    auto save_data = my::SaveData();
    my::SaveSystem().Fetch(save_data);

    _game_money->Initialize(save_data.GetMoney());
    _weapon_system->Initialize(save_data);
    _quick_change->Initialize({}, _weapon_system);
    _character->Initialize({});

    auto transform = def::Transform();
    transform.position = Mof::CVector3(4.0f, 0.0f, 0.0f);
    // EnemyÇèâä˙âªÇ∑ÇÈÇΩÇﬂÇ…ÉLÉÉÉbÉVÉÖ
    auto temp = ut::MakeSharedWithRelease<my::Enemy>();
    temp->AddObserver(shared_from_this());
    temp->Initialize(transform);
    _enemies.push_back(temp);

    this->AddElement(_character);
    this->AddElement(temp);
    return true;
}

bool my::GameManager::Input(void) {
    _game_money->Input();
    _quick_change->Input();

    _game_world.Input();
    return true;
}

bool my::GameManager::Update(float delta_time) {
    for (auto& ptr : _delete_actors) {
        this->RemoveElement(ptr);
    } // for
    _delete_actors.clear();


    _quick_change->Update();
    _stage.Update();


    _game_world.Update(delta_time);
    this->Collision();


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
    _character->Release();
    _stage.Release();

    //! save
    std::vector<std::string> weapon;
    _weapon_system->CreateAvailableWeaponNames(weapon);
    auto save_param = my::SaveDataParam(_game_money->GetValue(), weapon);
    my::SaveSystem().Save(save_param);

    _quick_change->Release();
    return true;
}