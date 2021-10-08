#include "Character.h"


std::shared_ptr<ratchet::actor::character::Character> ratchet::actor::character::Character::GetTalkedTarget(void) const {
    if (auto ptr = _talked_target.lock()) {
        return ptr;
    } // if
    return nullptr;
}

ratchet::actor::character::Character::Character() :
    super(),
    _talked_target() {
}

ratchet::actor::character::Character::~Character() {
}

void ratchet::actor::character::Character::SetTalkedTarget(const std::shared_ptr<ratchet::actor::character::Character>& ptr) {
    this->_talked_target = ptr;
}

bool ratchet::actor::character::Character::Release() {
    super::Release();
    _text_system_message_subject.Clear();
    _character_damage_apply_message_subject.Clear();
    return true;
}

void ratchet::actor::character::Character::Talk() {
}