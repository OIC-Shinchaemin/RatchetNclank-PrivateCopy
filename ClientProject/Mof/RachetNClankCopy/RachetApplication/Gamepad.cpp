#include "GamePad.h"


my::Gamepad::Gamepad() :
    _initialized(false),
    _gamepad() {
}

my::Gamepad::~Gamepad() {
}

my::Gamepad& my::Gamepad::GetInstance(void) {
    static my::Gamepad object;
    return object;
}

std::shared_ptr<Mof::CXGamePad> my::Gamepad::GetGamepad(void) const {
    _ASSERT_EXPR(_initialized, L"ゲームパッドが作成されていません");
    return this->_gamepad;
}

bool my::Gamepad::Create(void) {
    _gamepad = std::make_shared<Mof::CXGamePad>();
    // ゲームパッドの作成
    XGAMEPADCREATEINFO ci; ci.No = 0;
    _initialized = _gamepad->Create(&ci);
    return _initialized;
}

bool my::Gamepad::Release(void) {
    if (!_gamepad->Release()) {
        return false;
    } // if
    _gamepad.reset();
    _initialized = false;
    return true;
}

void my::Gamepad::RefreshKey(void) {
    _ASSERT_EXPR(_initialized, L"ゲームパッドが作成されていません");
    _gamepad->RefreshKey();
}