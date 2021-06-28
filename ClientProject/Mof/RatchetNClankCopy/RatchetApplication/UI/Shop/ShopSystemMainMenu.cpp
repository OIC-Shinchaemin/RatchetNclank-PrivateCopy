#include "ShopSystemMainMenu.h"

ratchet::ui::shop::ShopSystemMainMenu::ShopSystemMainMenu(const char* name) :
    super(name) {
}

void ratchet::ui::shop::ShopSystemMainMenu::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
}

void ratchet::ui::shop::ShopSystemMainMenu::SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr) {
}

bool ratchet::ui::shop::ShopSystemMainMenu::Initialize(void) {
    return false;
}

bool ratchet::ui::shop::ShopSystemMainMenu::Update(float delta_time) {
    return false;
}

bool ratchet::ui::shop::ShopSystemMainMenu::Render(void) {
    return false;
}
