#include "UIItem.h"


base::ui::UIItem::UIItem(const char* name) :
    _name(name),
    _position(),
    _texture(),
    _color(),
    _rectangle() {
}

base::ui::UIItem::~UIItem() {
    _texture.reset();
}

void base::ui::UIItem::SetPosition(Mof::CVector2 position) {
    this->_position = position;
}

void base::ui::UIItem::SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
    this->_texture = ptr;
}

void base::ui::UIItem::SetColor(const Mof::CVector4 color) {
    this->_color = color;
}

Mof::CVector2 base::ui::UIItem::GetPosition(void) const {
    return this->_position;
}

Mof::CVector2 base::ui::UIItem::GetSize(void) const {
    return Mof::CVector2();
}

Mof::CRectangle base::ui::UIItem::GetRectangle(void) const {
    auto rect = _rectangle;
    rect.Translation(_position);
    return rect;
}

bool base::ui::UIItem::Initialize(Mof::CVector2 pos, const std::shared_ptr<Mof::CTexture>& tex, const Mof::CVector4& color) {
    this->_position = pos;
    this->SetTexture(tex);
    this->SetColor(color);
    _rectangle = Mof::CRectangle(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight());
    return true;
}

bool base::ui::UIItem::DebugRender(void) {
    return true;
}