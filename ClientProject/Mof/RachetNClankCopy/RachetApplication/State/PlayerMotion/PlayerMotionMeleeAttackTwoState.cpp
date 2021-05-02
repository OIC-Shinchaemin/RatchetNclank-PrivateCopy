#include "PlayerMotionMeleeAttackTwoState.h"


state::PlayerMotionMeleeAttackTwoState::PlayerMotionMeleeAttackTwoState() :
    super() {
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::PlayerMotionMeleeAttackTwoState::~PlayerMotionMeleeAttackTwoState() {
}

const char* state::PlayerMotionMeleeAttackTwoState::GetName(void) const {
    return state::PlayerMotionStateType::kPlayerMotionMeleeAttackTwoState.c_str();
}

void state::PlayerMotionMeleeAttackTwoState::Update(float delta_time) {
}

void state::PlayerMotionMeleeAttackTwoState::Enter(void) {
    super::ChangeMotion(my::Player::MotionType::MeleeAttackTwo);
}

void state::PlayerMotionMeleeAttackTwoState::Exit(void) {
}