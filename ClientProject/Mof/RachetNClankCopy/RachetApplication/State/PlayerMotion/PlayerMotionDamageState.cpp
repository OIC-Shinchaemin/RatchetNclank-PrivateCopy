#include "PlayerMotionDamageState.h"


state::PlayerMotionDamageState::PlayerMotionDamageState() :
    super() {
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::PlayerMotionDamageState::~PlayerMotionDamageState() {
}

const char* state::PlayerMotionDamageState::GetName(void) const {
    return state::PlayerMotionStateType::kPlayerMotionDamageState.c_str();
}

void state::PlayerMotionDamageState::Update(float delta_time) {
}

void state::PlayerMotionDamageState::Enter(void) {
    super::ChangeMotion(my::Player::MotionType::DamageA);
}

void state::PlayerMotionDamageState::Exit(void) {
}