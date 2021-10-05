#include "UserActionHelperMenu.h"


ratchet::ui::UserActionHelperMenu::UserActionHelperMenu(const char* name) :
    super(name),
    _text(),
    _resource() {
    super::_position = Mof::CVector2(506.0f, 336.0f);
}

void ratchet::ui::UserActionHelperMenu::SetText(const std::string& text) {
    this->_text = text;
}

void ratchet::ui::UserActionHelperMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

bool ratchet::ui::UserActionHelperMenu::Update(float delta_time) {
    return true;
}

bool ratchet::ui::UserActionHelperMenu::Render(void) {
    auto pos = super::_position;
    //_text = "asfSADvbSd";
    //::CGraphicsUtilities::RenderString(pos.x, pos.y, _text.c_str());
    return true;
}