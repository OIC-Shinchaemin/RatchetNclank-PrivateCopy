#include "ShopSystem.h"

#include "../../UI/ShopSystemMenu.h"


void my::ShopSystem::Buy(void) {
    auto current = _items.at(_infomation.index);

    auto charge_info = my::ChargeInfo();
    charge_info.size = _infomation.count;
    charge_info.type = current.name;
    _buy_subject.Notify(charge_info);


    if (auto game_money = _game_money.lock()) {
        int price = _items.at(_infomation.index).price * _infomation.count;
        game_money->OnNotify(-price);
    } // if

    _infomation.count = 0;
    _infomation.select = false;
    _infomation.weapon = current.name;
    _info_subject.Notify(_infomation);
}

void my::ShopSystem::NotifyEquipmentWeaponMenu(void) {
    if (auto weapon_system = _weapon_system.lock()) {
        auto weapon = weapon_system->GetMechanicalWeapon(_infomation.weapon);
        auto info = my::Mechanical::Info();
        info.bullet_count = weapon->GetBulletCount();
        info.name = weapon->GetName();
        _equipment_weapon_menu_subject.Notify(info);
    } // if
}

void my::ShopSystem::NotifyGameMoneyMenu(void) {
    if (auto game_money = _game_money.lock()) {
        game_money_menu_subject.Notify(game_money->GetValue());
    } // if
}

my::ShopSystem::ShopSystem() :
    _infomation(),
    _subject(),
    _info_subject(),
    _equipment_weapon_menu_subject(),
    game_money_menu_subject(),
    _save_data(),
    _items(),
    _prev_weapon(),
    _weapon_system(),
    _game_money(),
    _resource(),
    _ui_canvas() {
}

my::ShopSystem::~ShopSystem() {
    _weapon_system.reset();
    _game_money.reset();
}

void my::ShopSystem::OnNotify(bool flag) {
    if (auto weapon_system = _weapon_system.lock()) {
        auto weapon = weapon_system->GetCurrentMechanicalWeapon();
        if (weapon) {
            _prev_weapon = weapon->GetName();
        } // if
    } // if

    auto current = _items.at(_infomation.index);
    _infomation.enable = flag;
    _infomation.weapon = _items.at(_infomation.index).name;
    _info_subject.Notify(_infomation);
    _subject.Notify(shared_from_this());

    if (auto weapon_system = _weapon_system.lock()) {
        auto weapon = weapon_system->GetMechanicalWeapon(_infomation.weapon);
        auto info = my::Mechanical::Info();
        info.bullet_count = weapon->GetBulletCount();
        info.name = weapon->GetName();
        _equipment_weapon_menu_subject.Notify(info);
    } // if
    if (auto game_money = _game_money.lock()) {
        game_money_menu_subject.Notify(game_money->GetValue());
    } // if
}

void my::ShopSystem::SetWeaponSystem(std::weak_ptr<my::WeaponSystem> ptr) {
    this->_weapon_system = ptr;
}

void my::ShopSystem::SetGameMoney(std::weak_ptr<my::GameMoney> ptr) {
    this->_game_money = ptr;
}

void my::ShopSystem::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::ShopSystem::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

my::Observable<const std::shared_ptr<my::ShopSystem>&>* my::ShopSystem::GetSubject(void) {
    return &this->_subject;
}

my::Observable<const my::ChargeInfo&>* my::ShopSystem::GetChargeInfoSubject(void) {
    return &this->_buy_subject;
}

bool my::ShopSystem::IsEnable(void) const {
    return this->_infomation.enable;
}

bool my::ShopSystem::Load(my::SaveData& in) {
    _save_data = in;

    auto& work = _save_data.GetAvailableMechanicalWeaponsAddress();
    _items.reserve(work.size());
    for (const auto& key : work) {
        int price = 0;
        if (key == "BombGlove") {
            price = 5;
        } // if
        else if (key == "Pyrocitor") {
            price = 1;
        } // else if
        else if (key == "Blaster") {
            price = 2;
        } // else if
        _items.emplace_back(my::ShopSystem::Item(key.c_str(), price, true));
    } // for
    return true;
}

bool my::ShopSystem::Initialize(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("ShopSystemMenu");
    } // if
    auto menu = std::make_shared< my::ShopSystemMenu>("ShopSystemMenu");
    _info_subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(_resource);
    menu->Initialize();
    if (auto canvas = _ui_canvas.lock()) {
        canvas->AddElement(menu);
    } // if

    if (auto canvas = _ui_canvas.lock()) {
        {
            auto temp = canvas->GetElement("EquipmentWeaponMenu");
            auto menu = std::dynamic_pointer_cast<my::Observer<const my::Mechanical::Info&>>(temp);
            _equipment_weapon_menu_subject.AddObserver(menu);
        }
        {
            auto temp = canvas->GetElement("GameMoneyMenu");
            auto menu = std::dynamic_pointer_cast<my::Observer<int>>(temp);
            game_money_menu_subject.AddObserver(menu);
        }
    } // if
    return true;
}

bool my::ShopSystem::Update(float delta_time) {
    if (!_infomation.enable) {
        _info_subject.Notify(_infomation);
        if (auto weapon_system = _weapon_system.lock()) {
            auto info = my::Mechanical::Info();
            if (_prev_weapon.has_value()) {
                auto prev = weapon_system->GetMechanicalWeapon(_prev_weapon.value());
                info.bullet_count = prev->GetBulletCount();
                info.name = prev->GetName();
            } // if
            _equipment_weapon_menu_subject.Notify(info);
        } // if
        if (auto game_money = _game_money .lock()) {
            game_money_menu_subject.Notify(game_money->GetValue());
        } // if
        return false;
    } // if

    if (::g_pInput->IsKeyPush(MOFKEY_M)) {
        if (!_infomation.select) {
            if (_infomation.enable) {
                _infomation.enable = false;
                _info_subject.Notify(_infomation);
            } // if
        } // if
    } // if

    if (_infomation.enable) {
        if (_infomation.select) {
            if (::g_pInput->IsKeyPush(MOFKEY_Z)) {
                this->Buy();
            } // if
            else if (::g_pInput->IsKeyPush(MOFKEY_M)) {
                _infomation.select = false;
                _infomation.count = 0;
                _info_subject.Notify(_infomation);
            } // else if
            else if (::g_pInput->IsKeyHold(MOFKEY_RIGHT)) {

                if (auto game_money = _game_money.lock()) {
                    int money = game_money->GetValue();
                    int price = _items.at(_infomation.index).price * (_infomation.count + 1);

                    if (price < money) {
                        _infomation.count++;
                    } // if
                } // if


                if (auto weapon_system = _weapon_system.lock()) {
                    int count = weapon_system->GetMechanicalWeapon(_items.at(_infomation.index).name)->GetBulletCountDecrased();
                    if (count < _infomation.count) {
                        _infomation.count = count;
                    } // if
                } // if

                _info_subject.Notify(_infomation);
            } // else if
            else if (::g_pInput->IsKeyHold(MOFKEY_LEFT)) {
                _infomation.count--;
                if (_infomation.count < 0) {
                    _infomation.count = 0;
                } // if

                _info_subject.Notify(_infomation);
            } // else if

        } // if
        else {
            if (::g_pInput->IsKeyPush(MOFKEY_Z)) {
                _infomation.select = true;
                _info_subject.Notify(_infomation);
            } // if
            else if (::g_pInput->IsKeyPush(MOFKEY_RIGHT)) {
                _infomation.index++;

                if (_items.size() - 1 < _infomation.index) {
                    _infomation.index = 0;
                } // if
                _infomation.weapon = _items.at(_infomation.index).name;
                _info_subject.Notify(_infomation);

                this->NotifyEquipmentWeaponMenu();
                this->NotifyGameMoneyMenu();

            } // else if
            else if (::g_pInput->IsKeyPush(MOFKEY_LEFT)) {
                _infomation.index--;

                if (_infomation.index < 0) {
                    _infomation.index = _items.size() - 1;
                } // if
                _infomation.weapon = _items.at(_infomation.index).name;
                _info_subject.Notify(_infomation);

                this->NotifyEquipmentWeaponMenu();
                this->NotifyGameMoneyMenu();


            } // else if
        } // else
    } // if
    return true;
}

bool my::ShopSystem::Release(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("ShopSystemMenu");
    } // if

    if (auto canvas = _ui_canvas.lock()) {
        {
            auto temp = canvas->GetElement("EquipmentWeaponMenu");
            auto menu = std::dynamic_pointer_cast<my::Observer<const my::Mechanical::Info&>>(temp);
            _equipment_weapon_menu_subject.RemoveObserver(menu);
        }
        {
            auto temp = canvas->GetElement("GameMoneyMenu");
            auto menu = std::dynamic_pointer_cast<my::Observer<int>>(temp);
            game_money_menu_subject.RemoveObserver(menu);
        }

    } // if

    return true;
}