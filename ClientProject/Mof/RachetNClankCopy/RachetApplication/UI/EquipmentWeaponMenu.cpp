#include "EquipmentWeaponMenu.h"


my::EquipmentWeaponMenu::EquipmentWeaponMenu(const char* name) :
    super(name),
    _info(),
    _tex_names(),
    _resource() {
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
}

void my::EquipmentWeaponMenu::OnNotify(const my::Mechanical::Info& info) {
    super::Notify(shared_from_this(), "Enable");
    //super::Notify()
    _info.name = info.name;
    _info.bullet_count = info.bullet_count;
}

void my::EquipmentWeaponMenu::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
}

bool my::EquipmentWeaponMenu::Render(void) {
    if (auto r = _resource.lock()) {
        auto it = _tex_names.find(_info.name);
        if (it != _tex_names.end()) {
            if (auto tex = r->Get<std::shared_ptr<Mof::CTexture>>(it->second.c_str())) {
                tex->Render(super::_position.x, super::_position.y);


                if (auto resource = _resource.lock()) {
                    auto font = resource->Get<std::shared_ptr<sip::CResourceFont>>("../Resource/font/kkm_analogtv.ttf\\KKM-アナログテレビフォント");
                    std::string text = "bullet count = ";
                    text += std::to_string(_info.bullet_count);
                    font->RenderString(super::_position.x, super::_position.y + 64.0f, text.c_str());
                } // if

            } // if
        } // if
    } // if
    return true;
}