#include "GamePauseSystemMenu.h"


my::GamePauseSystemMenu::GamePauseSystemMenu(const char* name) :
    super(name) {
}

void my::GamePauseSystemMenu::OnNotify(const my::GamePauseSystem::Info& info) {
    this->_infomation = info;
    if (info.enter) {
        super::Notify(shared_from_this(), "Enable");
    } // if
}

void my::GamePauseSystemMenu::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::GamePauseSystemMenu::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool my::GamePauseSystemMenu::Initialize(void) {
    return true;
}

bool my::GamePauseSystemMenu::Update(float delta_time) {
    if (_infomation.exit) {
        return false;
    } // if
    return true;
}

bool my::GamePauseSystemMenu::Render(void) {
    ::CGraphicsUtilities::RenderString(400.0f, 400.0f, "afaf");
    return true;
}
