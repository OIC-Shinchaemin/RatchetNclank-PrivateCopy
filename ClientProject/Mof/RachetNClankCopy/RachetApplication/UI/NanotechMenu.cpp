#include "NanotechMenu.h"


my::NanotechMenu::NanotechMenu(const char* name) :
    super(name),
    _hp_max(4),
    _hp(_hp_max),
    _ui_canvas() {
}

void my::NanotechMenu::OnNotify(int hp) {
    this->_hp = hp;
}

void my::NanotechMenu::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool my::NanotechMenu::Render(void) {
    auto pos = super::_position;

    float radius = 32.0f;
    for (int i = 0; i < _hp_max; i++) {
        if (i < _hp) {
            auto circle = Mof::CCircle(pos, radius);
            ::CGraphicsUtilities::RenderFillCircle(circle, def::color_rgba_u32::kYellow);
        } // if
        auto circle = Mof::CCircle(pos, radius);
        ::CGraphicsUtilities::RenderFillCircle(circle, super::_color.ToU32Color());
        pos.x += radius * 2.0f;
    } // for
    super::Render();
    return true;
}

my::NanotechMenuItem::NanotechMenuItem(const char* name) :
    super(name) {
}

bool my::NanotechMenuItem::Render(void) {
    return false;
}