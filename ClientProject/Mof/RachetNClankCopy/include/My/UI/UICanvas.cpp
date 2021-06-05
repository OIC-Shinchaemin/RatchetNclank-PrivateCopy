#include "UICanvas.h"


my::UICanvas::UICanvas() :
    _panels() {
}

my::UICanvas::~UICanvas() {
    _panels.clear();
}

void my::UICanvas::OnNotify(const std::shared_ptr<my::UIPanel>& ptr, const char* event) {
    //my::Observable<my::UICanvas>::Notify(shared_from_this(), event);
    if (event == "Enable") {
        if (std::find(_enable_list.begin(), _enable_list.end(), ptr) == _enable_list.end()) {
            _enable_list.push_back(ptr);
        } // if
    } // if
    else if (event == "Disable") {
        _disable_list.push_back(ptr);
    } // else if
}

my::UICanvas::ElemPtr my::UICanvas::GetElement(const std::string& name) const {
    auto it = std::find_if(_panels.begin(), _panels.end(), [name](const ElemPtr& ptr) {
        return ptr->GetName() == name;
    });
    if (it != _panels.end()) {
        return *it;
    } // if
    return nullptr;
}

void my::UICanvas::AddElement(const ElemPtr& elem) {
    elem->AddObserver(shared_from_this());
    _panels.push_back(elem);
}

void my::UICanvas::RemoveElement(const ElemPtr& elem) {
    elem->RemoveObserver(shared_from_this());
    ut::EraseRemove(_panels, elem);
}

bool my::UICanvas::RemoveElement(const std::string& name) {
    if (auto exist = this->GetElement(name); exist) {
        this->RemoveElement(exist);
        return true;
    } // if
    return false;
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
    /*
    for (auto& panel : _panels) {
        panel->Update(delta_time);
    } // for
    */

    for (auto ptr : _enable_list) {
        if (!ptr->Update(delta_time)) {
            _disable_list.push_back(ptr);
        } // if
    } // for

    for (auto ptr : _disable_list) {
        ut::EraseRemove(_enable_list, ptr);
    } // for
    _disable_list.clear();

    return true;
}

bool my::UICanvas::Render(void) {
    /*
    for (auto& panel : _panels) {
        panel->Render();
    } // for
    */
    for (auto ptr : _enable_list) {
        ptr->Render();
    } // for
    return true;
}