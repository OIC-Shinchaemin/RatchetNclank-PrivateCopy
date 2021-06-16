#include "ShopSystemElement.h"


ratchet::game::gamesystem::shop::ShopSystemElement::ShopSystemElement() :
    _resource(),
    _ui_canvas() {
}

ratchet::game::gamesystem::shop::ShopSystemElement::~ShopSystemElement() {
}

void ratchet::game::gamesystem::shop::ShopSystemElement::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
}

void ratchet::game::gamesystem::shop::ShopSystemElement::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
    this->_ui_canvas = ptr;
}

bool ratchet::game::gamesystem::shop::ShopSystemElement::Input(void) {
    return false;
}

bool ratchet::game::gamesystem::shop::ShopSystemElement::Update(void) {
    return false;
}