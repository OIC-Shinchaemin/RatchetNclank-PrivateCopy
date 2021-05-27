#include "HelpDeskMenu.h"


my::HelpDeskMenu::HelpDeskMenu(const char* name) :
    super(name) {
    super::_position = Mof::CVector2(20.0f, 500.0f);
}

void my::HelpDeskMenu::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

bool my::HelpDeskMenu::Update(float delta_time) {
    return false;
}

bool my::HelpDeskMenu::Render(void) {
    auto pos = super::_position;
    ::CGraphicsUtilities::RenderString(pos.x, pos.y, "››‚µ‚Ä‚­‚¾‚³‚¢");
    return true;
}