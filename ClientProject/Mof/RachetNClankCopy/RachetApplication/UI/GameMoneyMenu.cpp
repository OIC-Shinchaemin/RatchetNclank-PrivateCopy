#include "GameMoneyMenu.h"


my::GameMoneyMenu::GameMoneyMenu(const char* name) :
    super(name),
    _money(),
    _resource(),
    _ui_canvas() {
}

void my::GameMoneyMenu::OnNotify(int money) {
    this->_money = money;
}

void my::GameMoneyMenu::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource= ptr;
}

void my::GameMoneyMenu::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool my::GameMoneyMenu::Render(void) {
    ::CGraphicsUtilities::RenderString(800.0f,20.0f, "Money = %d" , _money);
    super::Render();
    return true;
}