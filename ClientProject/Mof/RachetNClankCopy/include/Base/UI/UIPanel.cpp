#include "UIPanel.h"


base::ui::UIPanel::UIPanel(const char* name) :
    _name(name),
    _position(),
    _items(),
    _texture(),
    _color(){
}

base::ui::UIPanel::~UIPanel() {
    _texture.reset();
    _items.clear();
}

void base::ui::UIPanel::OnNotify(const std::shared_ptr<base::ui::UIItem>& observable, const char* event) {
    base::core::Observable<const std::shared_ptr<base::ui::UIPanel>&, const char* >::Notify(shared_from_this(), event);
}

void base::ui::UIPanel::SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
    this->_texture = ptr;
}

void base::ui::UIPanel::SetPosition(Mof::CVector2 pos) {
    this->_position = pos;
}

void base::ui::UIPanel::SetColor(Mof::CVector4 color) {
    this->_color= color;
}

std::string base::ui::UIPanel::GetName(void) const {
    return this->_name;
}

Mof::CVector2 base::ui::UIPanel::GetPosition(void) const {
    return this->_position;
}

void base::ui::UIPanel::AddElement(const ElemPtr& elem) {
    elem->AddObserver(shared_from_this());
    this->_items.push_back(elem);
}

void base::ui::UIPanel::RemoveElement(const ElemPtr& elem) {
    elem->RemoveObserver(shared_from_this());
    ut::SwapPopback(_items, elem);
}

bool base::ui::UIPanel::Initialize(void) {
    return true;
}

bool base::ui::UIPanel::Update(float delta_time) {
    for (auto& item : _items) {
        item->Update(delta_time);
    } // for
    return true;
}

bool base::ui::UIPanel::Render(void) {
    if (auto tex = _texture.lock()) {
        tex->Render(_position.x, _position.y, _color.ToU32Color());
    } // if

    for (auto& item : _items) {
        item->Render();
        item->DebugRender();
    } // for
    return true;
}