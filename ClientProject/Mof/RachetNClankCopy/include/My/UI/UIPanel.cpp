#include "UIPanel.h"


my::UIPanel::UIPanel(const char* name) :
    _name(name),
    _position(),
    _items(),
    _texture(),
    _color(){
}

my::UIPanel::~UIPanel() {
    _texture.reset();
    _items.clear();
}

void my::UIPanel::OnNotify(const std::shared_ptr<my::UIItem>& observable, const char* event) {
    my::Observable<const std::shared_ptr<my::UIPanel>&, const char* >::Notify(shared_from_this(), event);
}

void my::UIPanel::SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
    this->_texture = ptr;
}

void my::UIPanel::SetPosition(Mof::CVector2 pos) {
    this->_position = pos;
}

void my::UIPanel::SetColor(Mof::CVector4 color) {
    this->_color= color;
}

std::string my::UIPanel::GetName(void) const {
    return this->_name;
}

Mof::CVector2 my::UIPanel::GetPosition(void) const {
    return this->_position;
}

void my::UIPanel::AddElement(const ElemPtr& elem) {
    elem->AddObserver(shared_from_this());
    this->_items.push_back(elem);
}

void my::UIPanel::RemoveElement(const ElemPtr& elem) {
    elem->RemoveObserver(shared_from_this());
    ut::SwapPopback(_items, elem);
}

bool my::UIPanel::Initialize(void) {
    return true;
}

bool my::UIPanel::Update(float delta_time) {
    for (auto& item : _items) {
        item->Update(delta_time);
    } // for
    return true;
}

bool my::UIPanel::Render(void) {
    if (auto tex = _texture.lock()) {
        tex->Render(_position.x, _position.y, _color.ToU32Color());
    } // if

    for (auto& item : _items) {
        item->Render();
        item->DebugRender();
    } // for
    return true;
}