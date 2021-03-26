#include "GameMoney.h"

#include "My/Core/Utility.h"


my::GameMoney::GameMoney() :
    _position(950.0f, 20.0f),
    _color(1.0f, 1.0f, 1.0f, 1.0f),
    _font_size(24.0f) {
    _texture = my::ResourceLocator::GetResource<Mof::CTexture>("../Resource/texture/money/money.png");
}

my::GameMoney::~GameMoney() {
    _font.Release();
}

std::uint32_t my::GameMoney::GetValue(void) const {
    return this->_value;
}

bool my::GameMoney::Initialize(uint32_t value) {
    _font.Create(_font_size, "");
    _value = value;
    return true;
}

bool my::GameMoney::Input(void) {
    if (::g_pInput->IsKeyHold(MOFKEY_UP)) {
        _value++;
    } // if
    else if (::g_pInput->IsKeyHold(MOFKEY_DOWN)) {
        _value--;
    } // else if


    return true;
}

bool my::GameMoney::Render(void) {
    if (auto tex = _texture.lock()) {
        tex->Render(_position.x, _position.y);
        auto pos = _position;
        pos.x -= _font_size * 0.5f * ut::GetDigit(_value) + ut::GetDigit(_value);
        _font.RenderString(pos.x, pos.y, std::to_string(_value).c_str());
    } // if
    return true;
}
