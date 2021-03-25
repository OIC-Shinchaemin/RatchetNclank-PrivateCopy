#include "UIPanel.h"


my::UIPanel::UIPanel() :
    _background(),
    _items(),
    _position() {
}

my::UIPanel::~UIPanel() {
    _background.reset();
    _items.clear();
}

void my::UIPanel::OnNotify(const std::shared_ptr<my::UIItem>& observable, const char* event) {
    my::Observable<my::UIPanel>::Notify(shared_from_this(), event);
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

bool my::UIPanel::Initialize(Mof::CVector2 pos) {
    this->_position = pos;
    return true;
}

bool my::UIPanel::Input(void) {
    for (auto& item : _items) {
        item->Input();
    } // for
    return true;
}

bool my::UIPanel::Update(float delta_time) {
    for (auto& item : _items) {
        item->Update(delta_time);
    } // for
    return true;
}

bool my::UIPanel::Render(void) {
    if (auto tex = _background.lock()) {
        tex->Render(_position.x, _position.y);
    } // if

    for (auto& item : _items) {
        item->Render();
        item->DebugRender();
    } // for
    return true;
}