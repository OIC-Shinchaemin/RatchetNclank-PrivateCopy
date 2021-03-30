#include "UICanvas.h"


my::UICanvas::UICanvas() :
    _panels(){
}

my::UICanvas::~UICanvas() {
    _panels.clear();
}

void my::UICanvas::OnNotify(const std::shared_ptr<my::UIPanel>& observable, const char* event) {
//    my::Observable<my::UICanvas>::Notify(shared_from_this(), event);
}

void my::UICanvas::AddElement(const ElemPtr& elem) {
    elem->AddObserver(shared_from_this());
    _panels.push_back(elem);
}

void my::UICanvas::RemoveElement(const ElemPtr& elem) {
    elem->RemoveObserver(shared_from_this());
    ut::EraseRemove(_panels, elem);
}

/*
bool my::UICanvas::Input(void) {
    if (!_panels.empty()) {
        _panels.back()->Input();
    } // if
    return true;
}
*/

bool my::UICanvas::Update(float delta_time) {
    for (auto& panel : _panels) {
        panel->Update(delta_time);
    } // for
    return true;
}

bool my::UICanvas::Render(void) {
    for (auto& panel : _panels) {
        panel->Render();
    } // for
    return true;
}