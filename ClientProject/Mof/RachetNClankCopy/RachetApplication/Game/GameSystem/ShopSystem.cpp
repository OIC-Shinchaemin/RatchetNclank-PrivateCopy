#include "ShopSystem.h"

#include "../../UI/ShopSystemMenu.h"


void my::ShopSystem::Buy(void) {
    //auto current = _items.at(_infomation.index);

    auto charge_info = my::ChargeInfo();
    charge_info.size = _infomation.count;
    //charge_info.type = current.name;
    charge_info.type = "Blaster";
    _buy_subject.Notify(charge_info);


    _infomation.count = 0;
    _infomation.select = false;
    _info_subject.Notify(_infomation);
}

my::ShopSystem::ShopSystem() :
    _infomation(),
    _subject(),
    _info_subject(),
    _resource(),
    _ui_canvas() {
}

my::ShopSystem::~ShopSystem() {
}

void my::ShopSystem::OnNotify(bool flag) {
    _infomation.enable = flag;
    _info_subject.Notify(_infomation);
    _subject.Notify(shared_from_this());
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
        _items.emplace_back(my::ShopSystem::Item(key.c_str(), true));
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
    return true;
}

bool my::ShopSystem::Update(float delta_time) {
    if (!_infomation.enable) {
        _info_subject.Notify(_infomation);
        return false;
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_M)) {
        if (_infomation.enable) {
            _infomation.enable = false;
            _info_subject.Notify(_infomation);
        } // if
    } // if


    /*
    if (_infomation.select) {
        if (::g_pInput->IsKeyPush(MOFKEY_P)) {
            this->Buy();
        } // if
        else if (::g_pInput->IsKeyPush(MOFKEY_O)) {
            _infomation.select = false;
            _infomation.count = 0;
            _info_subject.Notify(_infomation);
        } // else if
        else if (::g_pInput->IsKeyHold(MOFKEY_RIGHT)) {
            _infomation.count++;
            _info_subject.Notify(_infomation);
        } // else if
        else if (::g_pInput->IsKeyHold(MOFKEY_LEFT)) {
            _infomation.count--;
            _info_subject.Notify(_infomation);
        } // else if

    } // if
    else {
        if (::g_pInput->IsKeyPush(MOFKEY_RIGHT)) {
            _infomation.index++;
            _info_subject.Notify(_infomation);
        } // if
        else if (::g_pInput->IsKeyPush(MOFKEY_LEFT)) {
            _infomation.index--;
            _info_subject.Notify(_infomation);
        } // else if
    } // else
    */
    return true;
}

bool my::ShopSystem::Release(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("ShopSystemMenu");
    } // if
    return true;
}