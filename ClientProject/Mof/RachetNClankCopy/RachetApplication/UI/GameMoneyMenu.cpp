#include "GameMoneyMenu.h"


my::GameMoneyMenu::GameMoneyMenu(const char* name) :
    super(name),
    _money(),
    _show(true),
    _time_max(5.0f),
    _hide_timer(),
    _resource(),
    _ui_canvas() {
}

void my::GameMoneyMenu::OnNotify(int money) {
    this->_money = money;
    this->_show = true;
    this->_hide_timer.Initialize(_time_max, false);
}

void my::GameMoneyMenu::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::GameMoneyMenu::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool my::GameMoneyMenu::Initialize(void) {
    super::Initialize();
    super::_position = Mof::CVector2(700.0f, 0.0f);
    if (auto resource = _resource.lock()) {
        super::_texture = resource->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/money/money.png");
    } // if
    return true;
}

bool my::GameMoneyMenu::Update(float delta_time) {
    super::Update(delta_time);

    if (_hide_timer.Tick(delta_time)) {
        _show = false;
    } // if
    return true;
}

bool my::GameMoneyMenu::Render(void) {
    if (!this->_show) {
        return false;
    } // if
    
    if (auto tex = super::_texture.lock()) {
        auto pos = super::_position;
        tex->Render(pos.x, pos.y);
        pos.x += tex->GetWidth();
        ::CGraphicsUtilities::RenderString(pos.x, pos.y, "Money = %d", _money);
    } // if

    super::Render();
    return true;
}