#include "GamePad.h"


rachet::Gamepad::Gamepad() :
    _initialized(false),
    _gamepad() {
}

rachet::Gamepad::~Gamepad() {
}

rachet::Gamepad& rachet::Gamepad::GetInstance(void) {
    static rachet::Gamepad object;
    return object;
}

std::shared_ptr<Mof::CXGamePad> rachet::Gamepad::GetGamepad(void) const {
    _ASSERT_EXPR(_initialized, L"ゲームパッドが作成されていません");
    return this->_gamepad;
}

bool rachet::Gamepad::Create(void) {
    _gamepad = std::make_shared<Mof::CXGamePad>();
    // ゲームパッドの作成
    XGAMEPADCREATEINFO ci; ci.No = 0;
    _initialized = _gamepad->Create(&ci);
    return _initialized;
}

bool rachet::Gamepad::Release(void) {
    if (!_gamepad->Release()) {
        return false;
    } // if
    _gamepad.reset();
    _initialized = false;
    return true;
}

void rachet::Gamepad::RefreshKey(void) {
    _ASSERT_EXPR(_initialized, L"ゲームパッドが作成されていません");
    _gamepad->RefreshKey();
}