#include "GameMoney.h"

#include "Base/Core/Utility.h"
#include "../../UI/GameMoneyMenu.h"


ratchet::GameMoney::GameMoney() :
    _value(),
    _subject(),
    _resource(),
    _ui_canvas() {
}

ratchet::GameMoney::~GameMoney() {
    _resource.reset();
    _ui_canvas.reset();
}

void ratchet::GameMoney::OnNotify(int add_money) {
    this->_value += add_money;
    if (this->_value < 0) {
        this->_value = 0;
    } // if
    
    _subject.Notify(_value);
}

void ratchet::GameMoney::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::GameMoney::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

std::uint32_t ratchet::GameMoney::GetValue(void) const {
    return this->_value;
}

bool ratchet::GameMoney::Load(ratchet::SaveData& in) {
    _value = in.GetMoney();
    return true;
}

bool ratchet::GameMoney::Initialize(void) {
    _ASSERT_EXPR(!_resource.expired(), L"無効なポインタを保持しています");
    _ASSERT_EXPR(!_ui_canvas.expired(), L"無効なポインタを保持しています");

    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("GameMoneyMenu");
    } // if
    auto menu = std::make_shared< ratchet::GameMoneyMenu>("GameMoneyMenu");
    _subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(_resource);
    menu->Initialize();
    if (auto canvas = _ui_canvas.lock()) {
        canvas->AddElement(menu);
    } // if
    return true;
}

bool ratchet::GameMoney::Release(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("GameMoneyMenu");
    } // if
    return false;
}