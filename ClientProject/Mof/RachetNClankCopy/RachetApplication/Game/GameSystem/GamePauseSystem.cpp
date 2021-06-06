#include "GamePauseSystem.h"

#include "../../UI/GamePauseSystemMenu.h"


my::GamePauseSystem::GamePauseSystem() :
    _infomation(),
    _info_subject(),
    _item_index(),
    _ui_creator("GamePauseSystemMenu"){
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

bool my::GamePauseSystem::Initialize(void) {
    auto menu = _ui_creator.Create(super::GetUICanvas());
    menu->SetResourceManager(super::GetResource());
    _info_subject.AddObserver(menu);
    return true;
}

bool my::GamePauseSystem::Input(void) {
    return true;
}

bool my::GamePauseSystem::Update(float delta_time) {
    if (::g_pInput->IsKeyPull(MOFKEY_I)) {
        _infomation.exit = true;
        _info_subject.Notify(_infomation);
        _infomation.exit = false;
        return false;
    } // if
    return true;
}

bool my::GamePauseSystem::Release(void) {
    return true;
}