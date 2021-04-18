#include "PlayerMotionDamageState.h"


state::PlayerMotionDamageState::PlayerMotionDamageState() :
    super() {
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::PlayerMotionDamageState::~PlayerMotionDamageState() {
}

const char* state::PlayerMotionDamageState::GetName(void) const {
    return "PlayerMotionDamageState";
}

void state::PlayerMotionDamageState::Update(float delta_time) {
}

void state::PlayerMotionDamageState::Enter(void) {
    super::ChangeMotion(Player::MotionType::DamageDown);
}

void state::PlayerMotionDamageState::Exit(void) {
}