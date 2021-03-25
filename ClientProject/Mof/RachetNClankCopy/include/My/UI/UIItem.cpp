#include "UIItem.h"


my::UIItem::UIItem() :
    Event(),
    _name(),
    _texture(),
    _position(),
    _rectangle(),
    _color(1.0f, 1.0f, 1.0f, 1.0f) {
}

my::UIItem::UIItem(const std::string& name) {
}

my::UIItem::~UIItem() {
    _texture.reset();
}

void my::UIItem::Notify(const std::shared_ptr<my::UIItem>& shared_this, const char* event) {
    my::Observable<my::UIItem>::Notify(shared_this, event);
}

void my::UIItem::SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
    this->_texture = ptr;
}

void my::UIItem::SetBlendColor(const Mof::CVector4 color) {
    this->_color = color;
}

Mof::CRectangle my::UIItem::GetRectangle(void) const {
    auto rect = _rectangle;
    rect.Translation(_position);
    return rect;
}

bool my::UIItem::Initialize(Mof::CVector2 pos, const std::shared_ptr<Mof::CTexture>& tex, const Mof::CVector4& color) {
    this->_position = pos;
    this->SetTexture(tex);
    this->SetBlendColor(color);
    _rectangle = Mof::CRectangle(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight());
    return true;
}

bool my::UIItem::DebugRender(void) {
    return true;
}