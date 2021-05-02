#include "PlayerMotionMeleeAttackOneEndState.h"


state::PlayerMotionMeleeAttackOneEndState::PlayerMotionMeleeAttackOneEndState() :
    super() {
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::PlayerMotionMeleeAttackOneEndState::~PlayerMotionMeleeAttackOneEndState() {
}

const char* state::PlayerMotionMeleeAttackOneEndState::GetName(void) const {
    return state::PlayerMotionStateType::kPlayerMotionMeleeAttackOneEndState.c_str();
}

void state::PlayerMotionMeleeAttackOneEndState::Update(float delta_time) {
}

void state::PlayerMotionMeleeAttackOneEndState::Enter(void) {
    super::ChangeMotion(my::Player::MotionType::MeleeAttackOneEnd);
}

void state::PlayerMotionMeleeAttackOneEndState::Exit(void) {
}