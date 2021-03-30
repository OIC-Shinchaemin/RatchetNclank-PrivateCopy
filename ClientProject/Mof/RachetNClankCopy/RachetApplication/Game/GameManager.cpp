#include "GameManager.h"

#include "My/Core/Trait.h"
#include "My/Core/Utility.h"
#include "../GameSystem/Save/SaveData.h"
#include "../GameSystem/Save/SaveSystem.h"
#include "../Character/Enemy.h"
#include "../Character/Player.h"


void my::GameManager::AddElement(const std::shared_ptr<my::Character>& ptr) {
    if (ty::has_func_render<std::shared_ptr<my::Character>>()) {
        _renderer.AddElement(ptr);
    } // if
}

void my::GameManager::RemoveElement(const std::shared_ptr<my::Character>& ptr) {
    if (ty::has_func_render<std::shared_ptr<my::Character>>()) {
        _renderer.RemoveElement(ptr);
    } // if
}

void my::GameManager::Collision(void) {
    auto player = _character->GetPosition();
    for (auto& enemy: _enemies) {
        if (enemy->ContainInRecognitionRange(player)) {
            enemy->SetTarget(_character);
        } // if
        else {
            enemy->SetTarget(nullptr);
        } // else
    } // for
}

my::GameManager::GameManager() :
    _renderer(),
    _game_money(),
    _weapon_system(),
    _quick_change(),
    _stage(),
    _character(),
    _current_weapon() {
}

my::GameManager::~GameManager() {
}

bool my::GameManager::Initialize(void) {
    _stage.Initialize();

    _game_money = std::make_unique<my::GameMoney>();
    _weapon_system = std::make_shared<my::WeaponSystem>();
    _quick_change = std::make_shared<my::QuickChangeSystem>();
//    _character = std::make_shared<my::Character>();
    _character = std::make_shared<Player>();

    auto save_data = my::SaveData();
    my::SaveSystem().Fetch(save_data);

    _game_money->Initialize(save_data.GetMoney());
    _weapon_system->Initialize(save_data);
    _quick_change->Initialize({}, _weapon_system);
    _character->Initialize({});

    _current_weapon = _weapon_system->GetWeapon("OmniWrench");

    auto transform = def::Transform();
    transform.position = Mof::CVector3(1.0f, 0.0f, 0.0f);
    auto temp = std::make_shared<my::Enemy>();
    temp->Initialize(transform);
    _enemies.push_back(temp);

    _renderer.AddElement(_character);
    _renderer.AddElement(temp);
    return true;
}

bool my::GameManager::Input(void) {
    _game_money->Input();
    _quick_change->Input();

    if (::g_pInput->IsKeyPush(MOFKEY_1)) {
        _current_weapon = _weapon_system->GetWeapon("BombGlove");
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_2)) {
        _current_weapon = _weapon_system->GetWeapon("Pyrocitor");
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_3)) {
        _current_weapon = _weapon_system->GetWeapon("OmniWrench");
    } // if

    _character->Input();
    for (auto& ptr : _enemies) {
        ptr->Input();
    } // for

    return true;
}

bool my::GameManager::Update(float delta_time) {
    _quick_change->Update();
    _stage.Update();
    _character->Update(delta_time);
    for (auto& ptr : _enemies) {
        ptr->Update(delta_time);
    } // for
    _current_weapon->Update(delta_time);



    this->Collision();
    return true;
}

bool my::GameManager::Render(void) {
    _renderer.Render();

    _current_weapon->Render();

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