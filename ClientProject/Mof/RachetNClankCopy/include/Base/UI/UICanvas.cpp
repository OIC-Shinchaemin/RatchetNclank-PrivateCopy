#include "UICanvas.h"


base::ui::UICanvas::UICanvas() :
    _panels(),
    _enable_list(),
    _disable_list(){
}

base::ui::UICanvas::~UICanvas() {
    _panels.clear();
}

void base::ui::UICanvas::OnNotify(const std::shared_ptr<base::ui::UIPanel>& ptr, const char* event) {
    //base::core::Observable<base::ui::UICanvas>::Notify(shared_from_this(), event);
    if (event == "Enable") {
        if (std::find(_enable_list.begin(), _enable_list.end(), ptr) == _enable_list.end()) {
            _enable_list.push_back(ptr);
        } // if
    } // if
    else if (event == "Disable") {
        _disable_list.push_back(ptr);
    } // else if
}

base::ui::UICanvas::ElemPtr base::ui::UICanvas::GetElement(const std::string& name) const {
    auto it = std::find_if(_panels.begin(), _panels.end(), [name](const ElemPtr& ptr) {
        return ptr->GetName() == name;
    });
    if (it != _panels.end()) {
        return *it;
    } // if
    return nullptr;
}

void base::ui::UICanvas::AddElement(const ElemPtr& elem) {
    elem->AddObserver(shared_from_this());
    _panels.push_back(elem);
}

void base::ui::UICanvas::RemoveElement(const ElemPtr& elem) {
    elem->RemoveObserver(shared_from_this());
    ut::EraseRemove(_panels, elem);
    ut::EraseRemove(_enable_list, elem);
    ut::EraseRemove(_disable_list, elem);
}

bool base::ui::UICanvas::RemoveElement(const std::string& name) {
    if (auto exist = this->GetElement(name); exist) {
        this->RemoveElement(exist);
        return true;
    } // if
    return false;
}
/*
bool base::ui::UICanvas::Input(void) {
    for (auto ptr : _enable_list) {
        ptr->Input();
    } // for
    return true;
}
*/
bool base::ui::UICanvas::Update(float delta_time) {
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

bool base::ui::UICanvas::Render(void) {
    for (auto ptr : _enable_list) {
        ptr->Render();
    } // for
    return true;
}