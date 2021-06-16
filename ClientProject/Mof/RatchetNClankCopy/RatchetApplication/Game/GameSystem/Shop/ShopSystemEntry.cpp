#include "ShopSystemEntry.h"


ratchet::game::gamesystem::shop::ShopSystemEntry::ShopSystemEntry() :
    _ui_creator(""){
}

ratchet::game::gamesystem::shop::ShopSystemEntry::~ShopSystemEntry() {
}

bool ratchet::game::gamesystem::shop::ShopSystemEntry::Input(void) {
    puts("ratchet::game::gamesystem::shop::ShopSystemEntry::Input");
    return true;
}

bool ratchet::game::gamesystem::shop::ShopSystemEntry::Update(void) {
    puts("ratchet::game::gamesystem::shop::ShopSystemEntry::Update");
    return true;
}