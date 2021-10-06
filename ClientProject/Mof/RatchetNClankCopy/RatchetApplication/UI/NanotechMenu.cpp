#include "NanotechMenu.h"


ratchet::ui::NanotechMenu::NanotechMenu(const char* name) :
    super(name),
    _hp_max(4),
    _hp(_hp_max),
    _resource_manager(),
    _ui_canvas(),
//<<<<<<< Ex185_BulletActionFix
    _margin_x(12.0f){
    this->SetPosition(Mof::CVector2(800.0f, 24.0f));
//=======
//    _scale(ratchet::kWindowPerXGA) {
 //   this->SetPosition(Mof::CVector2(1600.0f, 60.0f));
//>>>>>>> MofLib
}

void ratchet::ui::NanotechMenu::OnNotify(int hp, int max) {
    super::Notify(shared_from_this(), "Enable");
    this->_hp = hp;
    this->_hp_max = max;
}

void ratchet::ui::NanotechMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource_manager = ptr;
}

void ratchet::ui::NanotechMenu::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool ratchet::ui::NanotechMenu::Update(float delta_time) {
    if (_hp < 0) {
        return false;
    } // if

    return true;
}

bool ratchet::ui::NanotechMenu::Render(void) {
    auto pos = super::_position;
    std::shared_ptr<Mof::CTexture> tex;
    std::shared_ptr<Mof::CTexture> empty_tex;
    if (auto r = _resource_manager.lock()) {
        tex = r->Get<std::shared_ptr<Mof::CTexture> >("../Resource/texture/nanotech/nanotech.png");
        empty_tex = r->Get<std::shared_ptr<Mof::CTexture> >("../Resource/texture/nanotech/nanotech_empty.png");
    } // if

    auto size = Mof::CVector2(tex->GetWidth(), tex->GetHeight());
    auto half_size = size * 0.5f * _scale;
    for (int i = 0; i < _hp_max; i++) {
        if (i < _hp) {
//<<<<<<< Ex185_BulletActionFix
            tex->Render(pos.x - half_size.x, pos.y - half_size.y);
        } // if
        pos.x += (tex->GetWidth() + _margin_x);
//=======
            //tex->Render(      pos.x - half_size.x, pos.y - half_size.y);
  //          tex->RenderScale(pos.x - half_size.x, pos.y - half_size.y, _scale);
    //    } // if
      //  pos.x += 48.0f * 2.0f;
//>>>>>>> MofLib

  } // for
    return true;
}

ratchet::ui::NanotechMenuItem::NanotechMenuItem(const char* name) :
    super(name) {
}

bool ratchet::ui::NanotechMenuItem::Render(void) {
    return false;
}