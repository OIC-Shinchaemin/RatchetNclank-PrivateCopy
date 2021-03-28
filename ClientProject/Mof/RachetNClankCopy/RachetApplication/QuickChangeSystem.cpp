#include "QuickChangeSystem.h"


my::QuickChangeSystem::QuickChangeSystem() :
    _position(50.0f, 200.0f),
    _color(1.0f, 1.0f, 1.0f, 0.0f),
    _state(State::Exit),
    _alpha(0.05f) ,
    _weapons(){
    _texture = my::ResourceLocator::GetResource<Mof::CTexture>("../Resource/texture/quick_change/background.png");
}

my::QuickChangeSystem::~QuickChangeSystem() {
}

bool my::QuickChangeSystem::Initialize(Mof::CVector2 pos, const std::shared_ptr<my::WeaponSystem>& weapon_system) {
    return true;
}

bool my::QuickChangeSystem::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_SPACE)) {
        _color = Mof::CVector4(1.0f, 1.0f, 1.0f, 0.25f);
        _state = State::Enter;
    } // if
    else if (::g_pInput->IsKeyPull(MOFKEY_SPACE)) {
        _state = State::Exit;
    } // else if

    if (_state == State::Enter) {
        _color.a += _alpha;
    } // if
    else if (_state == State::Exit) {
        _color.a -= _alpha * 3.0f;
    } // else if
    return true;
}

bool my::QuickChangeSystem::Render(void) {

    if (auto tex = _texture.lock()) {
        tex->Render(_position.x, _position.y, _color.ToU32Color());
    } // if
    return true;
}
