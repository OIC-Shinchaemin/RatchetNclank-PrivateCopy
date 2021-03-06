#include "HelpDeskMenu.h"


ratchet::ui::HelpDeskMenu::HelpDeskMenu(const char* name) :
    super(name) {
    super::_position = Mof::CVector2(10.0f, 10.0f);
}

void ratchet::ui::HelpDeskMenu::OnNotify(const ratchet::game::gamesystem::HelpDesk::Info& info) {
    super::Notify(shared_from_this(), "Enable");
    _infomation = info;
}

void ratchet::ui::HelpDeskMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

bool ratchet::ui::HelpDeskMenu::Update(float delta_time) {
    // 一定時間表示したらfalseを返す
    return true;
}

bool ratchet::ui::HelpDeskMenu::Render(void) {
    auto pos = super::_position;
    auto text = _infomation.text.c_str();
    ::CGraphicsUtilities::RenderString(pos.x + 1, pos.y + 1, def::color_rgba_u32::kBlack, "%s", text);
    ::CGraphicsUtilities::RenderString(pos.x , pos.y , def::color_rgba_u32::kWhite, "%s", text);
    return true;
}