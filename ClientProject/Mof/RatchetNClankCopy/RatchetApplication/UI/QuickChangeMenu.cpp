#include "QuickChangeMenu.h"


ratchet::ui::QuickChangeMenu::QuickChangeMenu(const char* name) :
    super(name),
    _distance(128.0f),
    _tex_names(),
    _resource() {
    //super::_position = Mof::CVector2(256.0f, 256.0f);
    super::_position = Mof::CVector2(506.0f, 336.0f);
    _tex_names.emplace("", "");
    _tex_names.emplace("BombGlove", "../Resource/texture/icon/bomb_glove.png");
    _tex_names.emplace("Pyrocitor", "../Resource/texture/icon/pyrocitor.png");
    _tex_names.emplace("Blaster", "../Resource/texture/icon/blaster.png");
    _tex_names.emplace("GloveOfDoom", "../Resource/texture/icon/glove_of_doom.png");
    _tex_names.emplace("MineGlove", "../Resource/texture/icon/mine_glove.png");
    _tex_names.emplace("Taunter", "../Resource/texture/icon/taunter.png");
    _tex_names.emplace("SuckCannon", "../Resource/texture/icon/suck_cannon.png");
    _tex_names.emplace("Devastator", "../Resource/texture/icon/devastator.png");
    _tex_names.emplace("Walloper", "../Resource/texture/icon/walloper.png");
    _tex_names.emplace("VisibombGun", "../Resource/texture/icon/visibomb_gun.png");
    _tex_names.emplace("DecoyGlove", "../Resource/texture/icon/decoy_glove.png");
    _tex_names.emplace("DroneDevice", "../Resource/texture/icon/drone_device.png");
    _tex_names.emplace("TeslaClaw", "../Resource/texture/icon/tesla_claw.png");
    _tex_names.emplace("MorphORay", "../Resource/texture/icon/morph_o_ray.png");
    _tex_names.emplace("RYNO", "../Resource/texture/icon/ryno.png");

    super::_items.reserve(8);
    for (int i = 0; i < 8; i++) {
        auto item = std::make_shared<ratchet::ui::QuickChangeMenuItem>("");

        float degree = 360.0f / 8;
        auto radian = math::Radian(degree * i);
        Mof::CVector2 pos = Mof::CVector2(_position + Mof::CVector2(std::cos(radian()) * _distance, -std::sin(radian()) * _distance));
        item->SetRectangle(Mof::CRectangle(0.0f, 0.0f, 64.0f, 64.0f));
        item->SetPosition(pos);
        super::_items.push_back(item);
    } // for
}

void ratchet::ui::QuickChangeMenu::OnNotify(const ratchet::QuickChangeSystem::Info& info) {
    super::Notify(shared_from_this(), "Enable");

    this->SetColor(info.color);
    _current_index = info.current_index;
}

void ratchet::ui::QuickChangeMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::ui::QuickChangeMenu::AddWeaponInfo(uint32_t index, const char* name) {
    _ASSERT_EXPR(index < super::_items.size(), L"範囲外アクセスです");
    auto item = super::_items.at(index);

    auto it = _tex_names.find(name);
    if (it != _tex_names.end()) {
        if (auto tex = _resource.lock()->Get<std::shared_ptr<Mof::CTexture> >(it->second.c_str())) {
            item->SetTexture(tex);
        } // if
    } // if
}

bool ratchet::ui::QuickChangeMenu::Update(float delta_time) {
    return true;
}

bool ratchet::ui::QuickChangeMenu::Render(void) {
    auto circle = Mof::CCircle(_position, 128.0f);
        // 選択中のものをわかりやすくしたい
    if (_current_index.has_value()) {
        //float current_angle = _current_angle.value();
        float current_angle = _current_index.value() * 45.0f;
        auto rect = Mof::CRectangle(0.0f, 0.0f, 64.0f, 64.0f);
        auto radian = math::Radian(current_angle);
        rect.Translation(-rect.GetBottomRight() * 0.5f);
        rect.Translation(super::_position + Mof::CVector2(std::cos(radian()) * _distance, -std::sin(radian()) * _distance));
        ::CGraphicsUtilities::RenderFillRect(rect, Mof::CVector4(1.0f, 1.0f, 0.0f, _color.a).ToU32Color());
    } // if

    ::CGraphicsUtilities::RenderCircle(circle, _color.ToU32Color());
    for (auto item : super::_items) {
        item->SetColor(_color);
        item->Render();
    } // for
    return true;
}

ratchet::ui::QuickChangeMenuItem::QuickChangeMenuItem(const char* name) :
    super(name) {
}

void ratchet::ui::QuickChangeMenuItem::SetRectangle(Mof::CRectangle rect) {
    super::_rectangle = rect;
}

bool ratchet::ui::QuickChangeMenuItem::Input(void) {
    return false;
}

bool ratchet::ui::QuickChangeMenuItem::Update(float delta_time) {
    return false;
}

bool ratchet::ui::QuickChangeMenuItem::Render(void) {
    auto rect = _rectangle;
    auto pos = _position - Mof::CVector2(rect.GetWidth() * 0.5f, rect.GetHeight() * 0.5f);

    rect.Translation(pos);
    ::CGraphicsUtilities::RenderRect(rect, Mof::CVector4(0.0f, 1.0f, 1.0f, _color.a).ToU32Color());
    if (auto tex = _texture.lock()) {
        tex->Render(pos.x, pos.y, _color.ToU32Color());
    } // if
    return true;
}