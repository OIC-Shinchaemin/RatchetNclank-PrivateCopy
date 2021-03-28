#include "GameManager.h"

#include "My/Core/Trait.h"
#include "My/Core/Utility.h"
#include "../Save/SaveData.h"
#include "../Save/SaveSystem.h"


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

my::GameManager::GameManager() :
    _character() {
}

my::GameManager::~GameManager() {
}

bool my::GameManager::Initialize(void) {
    _character = std::make_shared<my::Character>();
    _character->Initialize({});

    _quick_change = std::make_unique<my::QuickChangeSystem>();
    _game_money = std::make_unique<my::GameMoney>();
    _weapon_system = std::make_unique<my::WeaponSystem>();

    auto save_data = my::SaveData();
    my::SaveSystem().Fetch(save_data);

    _game_money->Initialize(save_data.GetMoney());
    _weapon_system->Initialize(save_data);

    _current_weapon = _weapon_system->GetWeapon("OmniWrench");
    return true;
}

bool my::GameManager::Input(void) {
    _quick_change->Input();
    _game_money->Input();


    if (::g_pInput->IsKeyPush(MOFKEY_1)) {
        _current_weapon = _weapon_system->GetWeapon("BombGlove");
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_2)) {
        _current_weapon = _weapon_system->GetWeapon("Pyrocitor");
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_3)) {
        _current_weapon = _weapon_system->GetWeapon("OmniWrench");
    } // if

    return true;
}

bool my::GameManager::Update(float delta_time) {
    return true;
}

bool my::GameManager::Render(void) {
    _current_weapon->Render();

    _quick_change->Render();
    _game_money->Render();
    return true;
}

bool my::GameManager::Release(void) {
    _character->Release();

    std::vector<std::string> weapon;
    _weapon_system->CreateAvailableWeaponNames(weapon);
    auto save_param = my::SaveDataParam(_game_money->GetValue(), weapon);
    my::SaveSystem().Save(save_param);
    return true;
}