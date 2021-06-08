#include "NanotechMenu.h"


my::NanotechMenu::NanotechMenu(const char* name) :
    super(name),
    _hp_max(4),
    _hp(_hp_max),
    _resource_manager(),
    _ui_canvas() {
}

void my::NanotechMenu::OnNotify(int hp) {
    super::Notify(shared_from_this(), "Enable");
    this->_hp = hp;
}

void my::NanotechMenu::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource_manager = ptr;
}

void my::NanotechMenu::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool my::NanotechMenu::Update(float delta_time) {
    if (_hp < 0) {
        return false;
    } // if

    return true;
}

bool my::NanotechMenu::Render(void) {
    auto pos = super::_position;
    std::shared_ptr<Mof::CTexture> tex;
    std::shared_ptr<Mof::CTexture> empty_tex;
    if (auto r = _resource_manager.lock()) {
        tex = r->Get<std::shared_ptr<Mof::CTexture> >("../Resource/texture/nanotech/nanotech.png");
        empty_tex = r->Get<std::shared_ptr<Mof::CTexture> >("../Resource/texture/nanotech/nanotech_empty.png");
    } // if


    auto size = Mof::CVector2(tex->GetWidth(), tex->GetHeight());
    auto half_size = size * 0.5f;
    float radius = 32.0f;
    for (int i = 0; i < _hp_max; i++) {
        empty_tex->Render(pos.x - half_size.x, pos.y - half_size.y);
        if (i < _hp) {
            auto circle = Mof::CCircle(pos, radius);
            ::CGraphicsUtilities::RenderFillCircle(circle, def::color_rgba_u32::kYellow);
            tex->Render(pos.x - half_size.x, pos.y - half_size.y);
        } // if
        
        auto circle = Mof::CCircle(pos, radius);
        ::CGraphicsUtilities::RenderFillCircle(circle, super::_color.ToU32Color());
        pos.x += radius * 2.0f;
    } // for
    return true;
}

my::NanotechMenuItem::NanotechMenuItem(const char* name) :
    super(name) {
}

bool my::NanotechMenuItem::Render(void) {
    return false;
}