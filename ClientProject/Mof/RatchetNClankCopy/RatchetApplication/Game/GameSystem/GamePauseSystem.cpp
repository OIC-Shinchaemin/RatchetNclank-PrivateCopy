#include "GamePauseSystem.h"

#include "../../UI/GamePauseSystemMenu.h"


ratchet::GamePauseSystem::GamePauseSystem() :
    _infomation(),
    _info_subject(),
    _ui_creator(typeid(decltype(_ui_creator)).name()) {
}

ratchet::GamePauseSystem::~GamePauseSystem() {
}

void ratchet::GamePauseSystem::OnNotify(bool flag) {
    super::OnNotify(flag);
    if (flag) {
        _infomation.Reset();

        _infomation.items = &_items;
        _infomation.enable = true;
        _info_subject.Notify(_infomation);
    } // if
}

base::core::Observable<const ratchet::GamePauseSystem::Info&>* ratchet::GamePauseSystem::GetInfoSubject(void) {
    return &this->_info_subject;
}

void ratchet::GamePauseSystem::AddItem(const std::shared_ptr<ElemType>& elem) {
    _infomation.items = &_items;
    _items.push_back(elem);
    _info_subject.Notify(_infomation);
}

bool ratchet::GamePauseSystem::IsActive(void) const {
    return this->_infomation.enable;
}

void ratchet::GamePauseSystem::Inactive(void) {
    this->_infomation.enable = false;
}

void ratchet::GamePauseSystem::Clear(void) {
    _items.clear();
}

bool ratchet::GamePauseSystem::Initialize(void) {
    _infomation.items = &_items;
    auto menu = _ui_creator.Create(super::GetUICanvas());
    menu->SetResourceManager(super::GetResource());
    _info_subject.AddObserver(menu);

    return true;
}

bool ratchet::GamePauseSystem::Input(void) {
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

bool ratchet::GamePauseSystem::Update(float delta_time) {
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

bool ratchet::GamePauseSystem::Release(void) {
    _items.clear();
    _info_subject.Clear();
    return true;
}

ratchet::GamePauseSystemItem::GamePauseSystemItem() {
}

ratchet::GamePauseSystemItem::GamePauseSystemItem(std::function<bool(void)> lambda) :
    _on_enter(lambda) {
}

ratchet::GamePauseSystemItem::~GamePauseSystemItem() {
}

void ratchet::GamePauseSystemItem::SetText(const char* text) {
    this->_text = text;
}

std::string ratchet::GamePauseSystemItem::GetText(void) const {
    return this->_text;
}

bool ratchet::GamePauseSystemItem::Execute(void) {
    return _on_enter();
}