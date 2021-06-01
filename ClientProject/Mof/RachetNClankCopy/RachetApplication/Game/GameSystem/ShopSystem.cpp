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
    _subject.Notify(_infomation);
}

my::ShopSystem::ShopSystem() :
    _infomation(),
    _subject(),
    _resource(),
    _ui_canvas() {
}

my::ShopSystem::~ShopSystem() {
}

void my::ShopSystem::OnNotify(bool flag) {
    _infomation.enable = flag;
    _subject.Notify(_infomation);
}

void my::ShopSystem::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::ShopSystem::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

my::Observable<const my::ChargeInfo&>* my::ShopSystem::GetChargeInfoSubject(void) {
    return &this->_buy_subject;
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
    _subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(_resource);
    menu->Initialize();
    if (auto canvas = _ui_canvas.lock()) {
        canvas->AddElement(menu);
    } // if
    return true;
}

bool my::ShopSystem::Update(float delta_time) {
    //std::cout << "update start" << "\n";

    if (::g_pInput->IsKeyPush(MOFKEY_L)) {
        _infomation.select = true;
        _subject.Notify(_infomation);
    } // if

    if (_infomation.select) {
        if (::g_pInput->IsKeyPush(MOFKEY_P)) {
            this->Buy();
        } // if
        else if (::g_pInput->IsKeyPush(MOFKEY_O)) {
            _infomation.select = false;
            _infomation.count = 0;
            _subject.Notify(_infomation);
        } // else if
        else if (::g_pInput->IsKeyHold(MOFKEY_RIGHT)) {
            _infomation.count++;
            _subject.Notify(_infomation);
        } // else if
        else if (::g_pInput->IsKeyHold(MOFKEY_LEFT)) {
            _infomation.count--;
            _subject.Notify(_infomation);
        } // else if

    } // if
    else {
        if (::g_pInput->IsKeyPush(MOFKEY_RIGHT)) {
            _infomation.index++;
            _subject.Notify(_infomation);
        } // if
        else if (::g_pInput->IsKeyPush(MOFKEY_LEFT)) {
            _infomation.index--;
            _subject.Notify(_infomation);
        } // else if
    } // else



      //std::cout << "update end" << "\n";
    return false;
}

bool my::ShopSystem::Release(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("ShopSystemMenu");
    } // if
    return true;
}