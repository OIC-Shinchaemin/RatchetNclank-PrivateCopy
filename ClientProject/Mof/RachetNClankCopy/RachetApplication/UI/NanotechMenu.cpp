#include "NanotechMenu.h"


my::NanotechMenu::NanotechMenu(const char* name) :
    super(name),
    _hp(4),
    _ui_canvas() {
}

void my::NanotechMenu::OnNotify(int hp) {
    _hp = hp;
}

void my::NanotechMenu::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool my::NanotechMenu::Render(void) {
    ::CGraphicsUtilities::RenderString(200.0f, 600.0f, "player  hp = %d", this->_hp);
    return true;
}

my::NanotechMenuItem::NanotechMenuItem(const char* name) :
    super(name) {
}

bool my::NanotechMenuItem::Render(void) {
    return false;
}
