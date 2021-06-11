#include "GamePauseSystem.h"

#include "../../UI/GamePauseSystemMenu.h"


ratchet::game::gamesystem::GamePauseSystem::GamePauseSystem() :
    _infomation(),
    _info_subject(),
    _ui_creator(typeid(decltype(_ui_creator)).name()) {
}

ratchet::game::gamesystem::GamePauseSystem::~GamePauseSystem() {
}

void ratchet::game::gamesystem::GamePauseSystem::OnNotify(bool flag) {
    super::OnNotify(flag);
    if (flag) {
        _infomation.Reset();

        _infomation.items = &_items;
        _infomation.enable = true;
        _info_subject.Notify(_infomation);
    } // if
}

base::core::Observable<const ratchet::game::gamesystem::GamePauseSystem::Info&>* ratchet::game::gamesystem::GamePauseSystem::GetInfoSubject(void) {
    return &this->_info_subject;
}

void ratchet::game::gamesystem::GamePauseSystem::AddItem(const std::shared_ptr<ElemType>& elem) {
    _infomation.items = &_items;
    _items.push_back(elem);
    _info_subject.Notify(_infomation);
}

bool ratchet::game::gamesystem::GamePauseSystem::IsActive(void) const {
    return this->_infomation.enable;
}

void ratchet::game::gamesystem::GamePauseSystem::Inactive(void) {
    this->_infomation.enable = false;
}

void ratchet::game::gamesystem::GamePauseSystem::Clear(void) {
    _items.clear();
}

bool ratchet::game::gamesystem::GamePauseSystem::Initialize(void) {
    _infomation.items = &_items;
    auto menu = _ui_creator.Create(super::GetUICanvas());
    menu->SetResourceManager(super::GetResource());
    _info_subject.AddObserver(menu);

    return true;
}

bool ratchet::game::gamesystem::GamePauseSystem::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_UP)) {
        if (_infomation.index.has_value()) {
            _infomation.index.value()++;
            if (_infomation.index.value() > _items.size() - 1) {
                _infomation.index = _items.size() - 1;
            } // if
            _infomation.index = _infomation.index.value();
            _info_subject.Notify(_infomation);
        } // if
        else {
            _infomation.index = 0;
        } // else
    } // if
    else if (::g_pInput->IsKeyPush(MOFKEY_DOWN)) {
        if (_infomation.index.has_value()) {
            _infomation.index.value()--;
            if (_infomation.index.value() < 0) {
                _infomation.index = 0;
            } // if
            _infomation.index = _infomation.index.value();
            _info_subject.Notify(_infomation);
        } // if
        else {
            _infomation.index = 0;
        } // else

    } // else if

    if (!_items.empty() && _infomation.index.has_value()) {
        if (::g_pInput->IsKeyPush(MOFKEY_Z) || ::g_pInput->IsKeyPush(MOFKEY_SPACE) || ::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
            _execute_list.push_back(_items.at(_infomation.index.value()));
        } // if
    } // if
    return true;
}

bool ratchet::game::gamesystem::GamePauseSystem::Update(float delta_time) {
    if (!_infomation.enable) {
        return false;
    } // if

    this->Input();
    if (!_execute_list.empty()) {
        for (auto ptr : _execute_list) {
            if (ptr->Execute()) {
            } // if
        } // for
        _execute_list.clear();
        _infomation.index.reset();
        this->_infomation.enable = false;
        
        _infomation.Reset();
        //_infomation.exit = true;
        _info_subject.Notify(_infomation);
        return false;
    } // if
    return true;
}

bool ratchet::game::gamesystem::GamePauseSystem::Release(void) {
    _items.clear();
    _info_subject.Clear();
    return true;
}

ratchet::game::gamesystem::GamePauseSystemItem::GamePauseSystemItem() {
}

ratchet::game::gamesystem::GamePauseSystemItem::GamePauseSystemItem(std::function<bool(void)> lambda) :
    _on_enter(lambda) {
}

ratchet::game::gamesystem::GamePauseSystemItem::~GamePauseSystemItem() {
}

void ratchet::game::gamesystem::GamePauseSystemItem::SetText(const char* text) {
    this->_text = text;
}

std::string ratchet::game::gamesystem::GamePauseSystemItem::GetText(void) const {
    return this->_text;
}

bool ratchet::game::gamesystem::GamePauseSystemItem::Execute(void) {
    return _on_enter();
}