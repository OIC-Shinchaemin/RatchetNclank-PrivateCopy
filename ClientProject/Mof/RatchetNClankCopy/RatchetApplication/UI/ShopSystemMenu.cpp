#include "ShopSystemMenu.h"


ratchet::ui::ShopSystemMenu::ShopSystemMenu(const char* name) :
    super(name),
    _show(true),
    _infomation(),
    _resource(),
    _ui_canvas() {
}

void ratchet::ui::ShopSystemMenu::OnNotify(const ratchet::game::gamesystem::ShopSystem::Info& info) {
    super::Notify(shared_from_this(), "Enable");
    _infomation = info;
}

void ratchet::ui::ShopSystemMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::ui::ShopSystemMenu::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool ratchet::ui::ShopSystemMenu::Initialize(void) {
    super::Initialize();
    super::_position = Mof::CVector2(500.0f, 300.0f);
    if (auto resource = _resource.lock()) {
        //super::_texture = resource->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/money/money.png");
    } // if
    return true;
}

bool ratchet::ui::ShopSystemMenu::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

bool ratchet::ui::ShopSystemMenu::Render(void) {
    if (!_infomation.enable) {
        return false;
    } // if

    auto rect = Mof::CRectangle(0.0f, 0.0f, 512.0f, 512.0f);
    auto pos = super::_position;
    rect.Translation(pos);
    ::CGraphicsUtilities::RenderFillRect(rect, def::color_rgba_u32::kRed);
    pos.y += 20.0f;

    if (_infomation.select) {
        ::CGraphicsUtilities::RenderString(pos.x, pos.y, "Mキー・Yボタンで戻る　\nLキー・Xボタンで買う");
    } // if
    else {
        ::CGraphicsUtilities::RenderString(pos.x, pos.y, "Mキー・Yボタンで閉じる　\nLキー・Xボタンで買う");
    } // else
    pos.y += 40.0f;

    

    pos.y += 20.0f;
    ::CGraphicsUtilities::RenderString(pos.x, pos.y, "選択中の武器　：　%s",
                                       _infomation.weapon.c_str());
    pos.y += 20.0f;
    if (_infomation.select) {
        ::CGraphicsUtilities::RenderString(pos.x, pos.y, "いくつ買う？ ：　%d",
                                           _infomation.count);
    } // if
    super::Render();
    return true;
}