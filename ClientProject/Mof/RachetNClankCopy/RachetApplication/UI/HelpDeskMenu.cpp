#include "HelpDeskMenu.h"


rachet::HelpDeskMenu::HelpDeskMenu(const char* name) :
    super(name) {
    super::_position = Mof::CVector2(10.0f, 10.0f);
}

void rachet::HelpDeskMenu::OnNotify(const rachet::HelpDesk::Info& info) {
    super::Notify(shared_from_this(), "Enable");
    _infomation = info;
}

void rachet::HelpDeskMenu::SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

bool rachet::HelpDeskMenu::Update(float delta_time) {
    // ˆê’èŽžŠÔ•\Ž¦‚µ‚½‚çfalse‚ð•Ô‚·
    return true;
}

bool rachet::HelpDeskMenu::Render(void) {
    auto pos = super::_position;
    auto text = _infomation.text.c_str();
    ::CGraphicsUtilities::RenderString(pos.x + 1, pos.y + 1, def::color_rgba_u32::kBlack, "%s", text);
    ::CGraphicsUtilities::RenderString(pos.x , pos.y , def::color_rgba_u32::kWhite, "%s", text);
    return true;
}