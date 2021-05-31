#include "MoneyMenu.h"


my::MoneyMenu::MoneyMenu(const char* name) :
    super(name),
    _money(),
    _ui_canvas() {
}

void my::MoneyMenu::OnNotify(int money) {
    this->_money = money;
}

void my::MoneyMenu::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool my::MoneyMenu::Render(void) {

    ::CGraphicsUtilities::RenderString(800.0f,20.0f, "Money");

    /*
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
    */
    super::Render();
    return true;
}