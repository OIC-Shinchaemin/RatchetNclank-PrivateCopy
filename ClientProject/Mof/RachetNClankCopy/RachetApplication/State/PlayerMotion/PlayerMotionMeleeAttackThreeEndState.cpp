#include "PlayerMotionMeleeAttackThreeEndState.h"


state::PlayerMotionMeleeAttackThreeEndState::PlayerMotionMeleeAttackThreeEndState() :
    super() {
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::PlayerMotionMeleeAttackThreeEndState::~PlayerMotionMeleeAttackThreeEndState() {
}

const char* state::PlayerMotionMeleeAttackThreeEndState::GetName(void) const {
    return state::PlayerMotionStateType::kPlayerMotionMeleeAttackThreeEndState.c_str();
}

void state::PlayerMotionMeleeAttackThreeEndState::Update(float delta_time) {
}

void state::PlayerMotionMeleeAttackThreeEndState::Enter(void) {
    super::ChangeMotion(my::Player::MotionType::MeleeAttackThreeEnd);
}

void state::PlayerMotionMeleeAttackThreeEndState::Exit(void) {
}