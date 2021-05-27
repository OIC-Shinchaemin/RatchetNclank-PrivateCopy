#include "HelpDesk.h"

#include "../../UI/HelpDeskMenu.h"


my::HelpDesk::HelpDesk() :
    _resource(),
    _ui_canvas() {
}

my::HelpDesk::~HelpDesk() {
}

void my::HelpDesk::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::HelpDesk::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool my::HelpDesk::Initialize(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("HelpDeskMenu");
    } // if
    auto menu = std::make_shared< my::HelpDeskMenu>("HelpDeskMenu");
//    _subject.AddObserver(menu);
    menu->SetColor(def::color_rgba::kCyan);
    menu->SetResourceManager(_resource);
    if (auto canvas = _ui_canvas.lock()) {
        canvas->AddElement(menu);
    } // if
    return true;
}

bool my::HelpDesk::Update(float delta_time) {
    return false;
}

bool my::HelpDesk::Release(void) {
    if (auto canvas = _ui_canvas.lock()) {
        canvas->RemoveElement("HelpDeskMenu");
    } // if
    return true;
}