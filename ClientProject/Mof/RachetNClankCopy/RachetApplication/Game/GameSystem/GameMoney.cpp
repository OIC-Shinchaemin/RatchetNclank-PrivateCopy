#include "GameMoney.h"

#include "My/Core/Utility.h"


my::GameMoney::GameMoney() :
    _position(950.0f, 20.0f),
    _color(1.0f, 1.0f, 1.0f, 1.0f),
    _font_size(24.0f),
    _resource(){
}

my::GameMoney::~GameMoney() {
    _font.Release();
}

void my::GameMoney::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

std::uint32_t my::GameMoney::GetValue(void) const {
    return this->_value;
}

bool my::GameMoney::Initialize(uint32_t value) {
    _ASSERT_EXPR(!_resource.expired(), L"–³Œø‚Èƒ|ƒCƒ“ƒ^‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚·");
    _font.Create(_font_size, "");
    _value = value;
    _texture = _resource.lock()->Get<std::shared_ptr<Mof::CTexture> >("../Resource/texture/money/money.png");

    return true;
}

bool my::GameMoney::Render(void) {
    if (auto tex = _texture.lock()) {
        tex->Render(_position.x, _position.y);
        auto pos = _position;
        pos.x -= _font_size * 0.5f * ut::GetDigit(_value) + ut::GetDigit(_value);
        const char* text = "ddd";

//        _font.RenderString(pos.x, pos.y, std::to_string(_value).c_str());
//        _font.RenderString(pos.x, pos.y, text);
        ::CGraphicsUtilities::RenderString(pos.x, pos.y, std::to_string(_value).c_str());
    } // if
    return true;
}
