#include "Character.h"


ratchet::actor::character::Character::Character() :
    super() {
}

ratchet::actor::character::Character::~Character() {
}

bool ratchet::actor::character::Character::Release() {
    super::Release();
    _text_system_message_subject.Clear();
    _character_damage_apply_message_subject.Clear();
    return true;
}

void ratchet::actor::character::Character::Talk() {
}