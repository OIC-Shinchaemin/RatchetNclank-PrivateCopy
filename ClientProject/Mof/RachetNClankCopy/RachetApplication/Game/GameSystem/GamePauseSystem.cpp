#include "GamePauseSystem.h"

#include "../../UI/GamePauseSystemMenu.h"


my::GamePauseSystem::GamePauseSystem() :
    _infomation(),
    _info_subject(),
    _item_index(),
    _ui_creator(typeid(decltype(_ui_creator)).name() ){
    _infomation.items = &_items;

    std::cout << "typeid(decltype(_ui_creator)).name()" << typeid(decltype(_ui_creator)).name() << "\n";
}

my::GamePauseSystem::~GamePauseSystem() {
}

void my::GamePauseSystem::OnNotify(bool flag) {
    super::OnNotify(flag);
    if (flag) {
        _infomation.enter = true;
        _info_subject.Notify(_infomation);
        _infomation.enter = false;
    } // if
}

my::Observable<const my::GamePauseSystem::Info&>* my::GamePauseSystem::GetInfoSubject(void) {
    return &this->_info_subject;
}

void my::GamePauseSystem::AddItem(const std::shared_ptr<ElemType>& elem) {
    _items.push_back(elem);
    _infomation.push_item = true;
    _info_subject.Notify(_infomation);
    _infomation.push_item = false;
}

bool my::GamePauseSystem::Initialize(void) {
    auto menu = _ui_creator.Create(super::GetUICanvas());
    menu->SetResourceManager(super::GetResource());
    _info_subject.AddObserver(menu);
    return true;
}

bool my::GamePauseSystem::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_UP)) {
        _item_index++;
        if (_item_index > _items.size() - 1) {
            _item_index = _items.size() - 1;
        } // if
        _infomation.index = _item_index;
        _info_subject.Notify(_infomation);
    } // if
    else if (::g_pInput->IsKeyPush(MOFKEY_DOWN)) {
        _item_index--;
        if (_item_index < 0) {
            _item_index = 0;
        } // if
        _infomation.index = _item_index;
        _info_subject.Notify(_infomation);
    } // else if

    if (!_items.empty()) {
        if (::g_pInput->IsKeyPush(MOFKEY_Z) || ::g_pInput->IsKeyPush(MOFKEY_SPACE) || ::g_pInput->IsKeyPush(MOFKEY_RETURN)) {
            _execute_list.push_back(_items.at(_item_index));
        } // if
    } // if
    return true;
}

bool my::GamePauseSystem::Update(float delta_time) {
    this->Input();
    if (!_execute_list.empty()) {
        for (auto ptr : _execute_list) {
            if (ptr->Execute()) {
            } // if
        } // for
        _execute_list.clear();
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