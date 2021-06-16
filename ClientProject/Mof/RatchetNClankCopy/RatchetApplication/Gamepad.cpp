#include "GamePad.h"


ratchet::Gamepad::Gamepad() :
    _initialized(false),
    _gamepad() {
}

ratchet::Gamepad::~Gamepad() {
}

ratchet::Gamepad& ratchet::Gamepad::GetInstance(void) {
    static ratchet::Gamepad object;
    return object;
}

std::shared_ptr<Mof::CXGamePad> ratchet::Gamepad::GetGamepad(void) const {
    _ASSERT_EXPR(_initialized, L"�Q�[���p�b�h���쐬����Ă��܂���");
    return this->_gamepad;
}

bool ratchet::Gamepad::Create(void) {
    _gamepad = std::make_shared<Mof::CXGamePad>();
    // �Q�[���p�b�h�̍쐬
    XGAMEPADCREATEINFO ci; ci.No = 0;
    _initialized = _gamepad->Create(&ci);
    return _initialized;
}

bool ratchet::Gamepad::Release(void) {
    if (!_gamepad->Release()) {
        return false;
    } // if
    _gamepad.reset();
    _initialized = false;
    return true;
}

void ratchet::Gamepad::RefreshKey(void) {
    _ASSERT_EXPR(_initialized, L"�Q�[���p�b�h���쐬����Ă��܂���");
    _gamepad->RefreshKey();
}