#include "GameManager.h"

#include "GameSystem/Save/SaveData.h"
#include "GameSystem/Save/SaveSystem.h"


my::GameManager::GameManager() :
    _weapon_system(std::make_shared<my::WeaponSystem>()),
    _quick_change(std::make_shared<my::QuickChangeSystem>()),
    _help_desk(std::make_shared<my::HelpDesk>()),
    _game_money(std::make_shared<my::GameMoney>()),
    _resource(),
    _ui_canvas() {
}

my::GameManager::~GameManager() {
}

void my::GameManager::SetResourceManager(const std::shared_ptr<my::ResourceMgr>& ptr) {
    this->_resource = ptr;
}

void my::GameManager::SetUICanvas(const std::shared_ptr<my::UICanvas>& ptr) {
    this->_ui_canvas = ptr;
}

std::shared_ptr<my::WeaponSystem> my::GameManager::GetWeaponSystem(void) const {
    return this->_weapon_system;
}

std::shared_ptr<my::QuickChangeSystem> my::GameManager::GetQuickChange(void) const {
    return this->_quick_change;
}

std::shared_ptr<my::HelpDesk> my::GameManager::GetHelpDesk(void) const {
    return this->_help_desk;
}

std::shared_ptr<my::GameMoney> my::GameManager::GetGameMoney(void) const {
    return this->_game_money;
}

void my::GameManager::GameSystemLoad(void) {
    auto save_data = my::SaveData();
    my::SaveSystem().Fetch(save_data);
    _weapon_system->Load(save_data);
    _game_money->Load(save_data);
}

bool my::GameManager::Initialize(void) {
    _weapon_system->SetResourceManager(_resource);
    _weapon_system->SetUICanvas(_ui_canvas);
    _quick_change->SetResourceManager(_resource);
    _quick_change->SetUICanvas(_ui_canvas);
    _help_desk->SetResourceManager(_resource);
    _help_desk->SetUICanvas(_ui_canvas);
    _game_money->SetResourceManager(_resource);
    _game_money->SetUICanvas(_ui_canvas);
    return true;
}

bool my::GameManager::Update(void) {
    _quick_change->Update();
    return true;
}

bool my::GameManager::Release(void) {
    _weapon_system.reset();
    _quick_change.reset();
    _help_desk.reset();
    _game_money.reset();
    _resource.reset();
    _ui_canvas.reset();
    return true;
}

void my::GameManager::GameSystemRelease(void) {
   //! save
    std::vector<std::string> weapon;
    _weapon_system->CreateAvailableMechanicalWeaponNames(weapon);
    auto save_param = my::SaveDataParam(0, weapon);
    my::SaveSystem().Save(save_param);
    _quick_change->Release();
    _weapon_system->Release();
    _help_desk->Release();
    _game_money->Release();
}