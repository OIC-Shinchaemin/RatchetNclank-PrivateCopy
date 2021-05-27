#include "HelpDeskMenu.h"


my::HelpDeskMenu::HelpDeskMenu(const char* name) :
    super(name) {
    super::_position = Mof::CVector2(20.0f, 500.0f);
}

void my::HelpDeskMenu::OnNotify(const my::HelpDesk::Info& info) {
    _infomation = info;
}

void my::HelpDeskMenu::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

bool my::HelpDeskMenu::Update(float delta_time) {
    return false;
}

bool my::HelpDeskMenu::Render(void) {
    auto pos = super::_position;
    auto text = _infomation.text.c_str();
    ::CGraphicsUtilities::RenderString(pos.x, pos.y, "%s", text);
    return true;
}