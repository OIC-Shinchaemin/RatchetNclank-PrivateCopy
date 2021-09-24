#include "GameMoney.h"

#include "Base/Core/Utility.h"
#include "../../UI/GameMoneyMenu.h"

#include "../../Event/BridgeEvent.h"


ratchet::game::gamesystem::GameMoney::GameMoney() :
    _value(),
    _value_max(40),
    _subject(),
    _resource(),
    _ui_canvas(),
    _event_manager() {
}

ratchet::game::gamesystem::GameMoney::~GameMoney() {
    _resource.reset();
    _ui_canvas.reset();
    _event_manager.reset();
}

void ratchet::game::gamesystem::GameMoney::OnNotify(int add_money) {
    this->_value += add_money;
    if (this->_value < 0) {
        this->_value = 0;
    } // if

    auto message = game::gamesystem::GameMoneyMessage();
    message.money = _value;
    message.money_max = _value_max;

    if (message.money > message.money_max) {
        if (auto e = _event_manager.lock()) {
            auto bridge_event = e->CreateGameEvent<ratchet::event::BridgeEvent>();
            bridge_event->Initialize();
        } // if
    } // if
    _subject.Notify(message);
}

void ratchet::game::gamesystem::GameMoney::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::game::gamesystem::GameMoney::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

void ratchet::game::gamesystem::GameMoney::SetEventManager(std::weak_ptr<ratchet::event::EventManager> ptr) {
    this->_event_manager = ptr;
}

std::uint32_t ratchet::game::gamesystem::GameMoney::GetValue(void) const {
    return this->_value;
}

bool ratchet::game::gamesystem::GameMoney::Load(ratchet::game::gamesystem::save::SaveData& in) {
    _value = in.GetMoney();
    return true;
}

bool ratchet::game::gamesystem::GameMoney::Initialize(void) {
    _ASSERT_EXPR(!_resource.expired(), L"無効なポインタを保持しています");
    _ASSERT_EXPR(!_ui_canvas.expired(), L"無効なポインタを保持しています");

    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("GameMoneyMenu");
    } // if
    auto menu = std::make_shared< ratchet::ui::GameMoneyMenu>("GameMoneyMenu");
    _subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(_resource);
    menu->Initialize();
    if (auto canvas = _ui_canvas.lock()) {
        canvas->AddElement(menu);
    } // if
    return true;
}

bool ratchet::game::gamesystem::GameMoney::Release(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("GameMoneyMenu");
    } // if
    return false;
}