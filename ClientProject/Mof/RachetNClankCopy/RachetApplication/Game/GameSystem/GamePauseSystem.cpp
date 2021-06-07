#include "GamePauseSystem.h"

#include "../../UI/GamePauseSystemMenu.h"


my::GamePauseSystem::GamePauseSystem() :
    _infomation(),
    _info_subject(),
    //_item_index(),
    _ui_creator(typeid(decltype(_ui_creator)).name()) {
}

my::GamePauseSystem::~GamePauseSystem() {
}

void my::GamePauseSystem::OnNotify(bool flag) {
    super::OnNotify(flag);
    if (flag) {
        _infomation.Reset();


        puts("");
        _infomation.items = &_items;
        _infomation.enable = true;
        //_infomation.enter = true;
        _info_subject.Notify(_infomation);
        //_infomation.enter = false;
    } // if
}

my::Observable<const my::GamePauseSystem::Info&>* my::GamePauseSystem::GetInfoSubject(void) {
    return &this->_info_subject;
}

void my::GamePauseSystem::AddItem(const std::shared_ptr<ElemType>& elem) {
    _infomation.items = &_items;

    _items.push_back(elem);
    //_infomation.push_item = true;
    _info_subject.Notify(_infomation);
    //_infomation.push_item = false;
}

bool my::GamePauseSystem::IsActive(void) const {
    return this->_infomation.enable;
}

void my::GamePauseSystem::Inactive(void) {
    this->_infomation.enable = false;
}

void my::GamePauseSystem::Clear(void) {
    _items.clear();
}

bool my::GamePauseSystem::Initialize(void) {
    _infomation.items = &_items;
    auto menu = _ui_creator.Create(super::GetUICanvas());
    menu->SetResourceManager(super::GetResource());
    _info_subject.AddObserver(menu);

    return true;
}

bool my::GamePauseSystem::Input(void) {
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

bool my::GamePauseSystem::Update(float delta_time) {
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

bool my::GamePauseSystem::Release(void) {
    _items.clear();
    _info_subject.Clear();
    return true;
}

my::GamePauseSystemItem::GamePauseSystemItem() {
}

my::GamePauseSystemItem::GamePauseSystemItem(std::function<bool(void)> lambda) :
    _on_enter(lambda) {
}

my::GamePauseSystemItem::~GamePauseSystemItem() {
}

void my::GamePauseSystemItem::SetText(const char* text) {
    this->_text = text;
}

std::string my::GamePauseSystemItem::GetText(void) const {
    return this->_text;
}

bool my::GamePauseSystemItem::Execute(void) {
    return _on_enter();
}