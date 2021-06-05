#include "GameManager.h"

#include "GameSystem/Save/SaveData.h"
#include "GameSystem/Save/SaveSystem.h"


my::GameManager::GameManager() :
    _update_system(),
    _disable_systems(),
    _weapon_system(std::make_shared<my::WeaponSystem>()),
    _quick_change(std::make_shared<my::QuickChangeSystem>()),
    _help_desk(std::make_shared<my::HelpDesk>()),
    _game_money(std::make_shared<my::GameMoney>()),
    _shop_system(std::make_shared<my::ShopSystem>()),
    _option_system(std::make_shared<my::OptionSystem>()),
    _resource(),
    _ui_canvas() {
    _shop_system->GetChargeInfoSubject()->AddObserver(_weapon_system);
    _shop_system->SetWeaponSystem(_weapon_system);
    _shop_system->SetGameMoney(_game_money);
}

my::GameManager::~GameManager() {
}

void my::GameManager::OnNotify(const std::shared_ptr<my::GameSystem>& ptr) {
    _update_system.push_back(ptr);
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

std::shared_ptr<my::ShopSystem> my::GameManager::GetShopSystem(void) const {
    return this->_shop_system;
}

std::shared_ptr<my::OptionSystem> my::GameManager::GetOptionSystem(void) const {
    return this->_option_system;
}

void my::GameManager::GameSystemLoad(void) {
    auto save_data = my::SaveData();
    my::SaveSystem().Fetch(save_data);
    _weapon_system->Load(save_data);
    _game_money->Load(save_data);
    _shop_system->Load(save_data);
}

bool my::GameManager::Initialize(void) {
    _quick_change->GetSubject()->AddObserver(shared_from_this());
    _shop_system->GetSubject()->AddObserver(shared_from_this());
    _option_system->GetSubject()->AddObserver(shared_from_this());

    _weapon_system->SetResourceManager(_resource);
    _weapon_system->SetUICanvas(_ui_canvas);
    _quick_change->SetResourceManager(_resource);
    _quick_change->SetUICanvas(_ui_canvas);
    _help_desk->SetResourceManager(_resource);
    _help_desk->SetUICanvas(_ui_canvas);
    _game_money->SetResourceManager(_resource);
    _game_money->SetUICanvas(_ui_canvas);
    _shop_system->SetResourceManager(_resource);
    _shop_system->SetUICanvas(_ui_canvas);
    _option_system->SetResourceManager(_resource);
    _option_system->SetUICanvas(_ui_canvas);
    return true;
}

bool my::GameManager::Release(void) {
    _shop_system->GetChargeInfoSubject()->RemoveObserver(_weapon_system);
    _update_system.clear();
    _disable_systems.clear();
    _shop_system.reset();
    _weapon_system.reset();
    _quick_change.reset();
    _help_desk.reset();
    _option_system.reset();
    _game_money.reset();
    _resource.reset();
    _ui_canvas.reset();
    return true;
}

bool my::GameManager::Update(float delta_time) {
    for (auto ptr : _update_system) {
        if (!ptr->Update(delta_time)) {
            _disable_systems.push_back(ptr);
        } // if
    } // for

    for (auto ptr : _disable_systems) {
        ut::EraseRemove(_update_system, ptr);
    } // for
    _disable_systems.clear();
    return true;
}

void my::GameManager::GameSystemRelease(void) {
   //! save
    std::vector<std::string> weapon;
    _weapon_system->CreateAvailableMechanicalWeaponNames(weapon);

    auto save_param = my::SaveDataParam(_game_money->GetValue(), weapon);
    my::SaveSystem().Save(save_param);
    _update_system.clear();
    _disable_systems.clear();
    
    _shop_system->Release();
    _quick_change->Release();
    _weapon_system->Release();
    _help_desk->Release();
    _option_system->Release();
    _game_money->Release();

    _shop_system->GetSubject()->RemoveObserver(shared_from_this());
    _quick_change->GetSubject()->RemoveObserver(shared_from_this());
    _option_system->GetSubject()->RemoveObserver(shared_from_this());
}