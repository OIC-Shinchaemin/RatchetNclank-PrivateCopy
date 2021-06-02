#include "ShopSystemMenu.h"


my::ShopSystemMenu::ShopSystemMenu(const char* name) :
    super(name),
    _show(true),
    _infomation(),
    _resource(),
    _ui_canvas() {
}

void my::ShopSystemMenu::OnNotify(const my::ShopSystem::Info& info) {
    _infomation = info;
}

void my::ShopSystemMenu::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void my::ShopSystemMenu::SetUICanvas(std::weak_ptr<my::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool my::ShopSystemMenu::Initialize(void) {
    super::Initialize();
    super::_position = Mof::CVector2(500.0f, 300.0f);
    if (auto resource = _resource.lock()) {
        //super::_texture = resource->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/money/money.png");
    } // if
    return true;
}

bool my::ShopSystemMenu::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

bool my::ShopSystemMenu::Render(void) {
    if (!_infomation.enable) {
        return false;
    } // if

    auto rect = Mof::CRectangle(0.0f, 0.0f, 512.0f, 512.0f);
    auto pos = super::_position;
    rect.Translation(pos);
    ::CGraphicsUtilities::RenderFillRect(rect, def::color_rgba_u32::kRed);
    pos.y += 20.0f;

    if (_infomation.select) {
        ::CGraphicsUtilities::RenderString(pos.x, pos.y, "Mキー・△で戻る　Lキー・○✕で買う");
    } // if
    else {
        ::CGraphicsUtilities::RenderString(pos.x, pos.y, "Mキー・△で閉じる　Lキー・○✕で買う");
    } // else
    pos.y += 20.0f;
    ::CGraphicsUtilities::RenderString(pos.x, pos.y, "Shop index = %d  count = %d select = %d",
                                       _infomation.index, _infomation.count, _infomation.select);
    pos.y += 20.0f;
    ::CGraphicsUtilities::RenderString(pos.x, pos.y, "Weapon = %s",
                                       _infomation.weapon.c_str());


    super::Render();
    return true;
}