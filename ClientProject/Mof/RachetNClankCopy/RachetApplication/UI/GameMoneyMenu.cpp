#include "GameMoneyMenu.h"


ratchet::GameMoneyMenu::GameMoneyMenu(const char* name) :
    super(name),
    _money(),
    _show(true),
    _time_max(5.0f),
    _hide_timer(),
    _resource(),
    _ui_canvas() {
}

void ratchet::GameMoneyMenu::OnNotify(int money) {
    super::Notify(shared_from_this(), "Enable");
    
    this->_money = money;
    this->_show = true;
    this->_hide_timer.Initialize(_time_max, false);
}

void ratchet::GameMoneyMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::GameMoneyMenu::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool ratchet::GameMoneyMenu::Initialize(void) {
    super::Initialize();
    super::_position = Mof::CVector2(920.0f, 48.0f);
    if (auto resource = _resource.lock()) {
        super::_texture = resource->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/money/money.png");
    } // if
    return true;
}

bool ratchet::GameMoneyMenu::Update(float delta_time) {
    super::Update(delta_time);

    if (_hide_timer.Tick(delta_time)) {
        _show = false;
    } // if
    return true;
}

bool ratchet::GameMoneyMenu::Render(void) {
    if (!this->_show) {
        return false;
    } // if
    
    if (auto tex = super::_texture.lock()) {
        auto pos = super::_position;
        tex->RenderScale(pos.x, pos.y, 0.5f);
        pos.x += tex->GetWidth() * 0.5f;
        ::CGraphicsUtilities::RenderString(pos.x + 1, pos.y + 1  , def::color_rgba_u32::kBlack, " %d", _money);
        ::CGraphicsUtilities::RenderString(pos.x, pos.y , def::color_rgba_u32::kWhite, " %d", _money);
    } // if

    //super::Render();
    return true;
}