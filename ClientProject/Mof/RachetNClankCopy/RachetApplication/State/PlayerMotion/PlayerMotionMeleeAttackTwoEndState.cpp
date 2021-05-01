#include "PlayerMotionMeleeAttackTwoEndState.h"


state::PlayerMotionMeleeAttackTwoEndState::PlayerMotionMeleeAttackTwoEndState() :
    super() {
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::PlayerMotionMeleeAttackTwoEndState::~PlayerMotionMeleeAttackTwoEndState() {
}

const char* state::PlayerMotionMeleeAttackTwoEndState::GetName(void) const {
    return state::PlayerMotionStateType::kPlayerMotionMeleeAttackTwoEndState.c_str();
}

void state::PlayerMotionMeleeAttackTwoEndState::Update(float delta_time) {
}

void state::PlayerMotionMeleeAttackTwoEndState::Enter(void) {
    super::ChangeMotion(my::Player::MotionType::MeleeAttackTwoEnd);
}

void state::PlayerMotionMeleeAttackTwoEndState::Exit(void) {
}