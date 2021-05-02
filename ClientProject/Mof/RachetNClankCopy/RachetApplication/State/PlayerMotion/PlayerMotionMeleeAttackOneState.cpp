#include "PlayerMotionMeleeAttackOneState.h"


state::PlayerMotionMeleeAttackOneState::PlayerMotionMeleeAttackOneState() :
    super() {
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::PlayerMotionMeleeAttackOneState::~PlayerMotionMeleeAttackOneState() {
}

const char* state::PlayerMotionMeleeAttackOneState::GetName(void) const {
    return state::PlayerMotionStateType::kPlayerMotionMeleeAttackOneState.c_str();
}

void state::PlayerMotionMeleeAttackOneState::Update(float delta_time) {
}

void state::PlayerMotionMeleeAttackOneState::Enter(void) {
    super::ChangeMotion(my::Player::MotionType::MeleeAttackOne);
}

void state::PlayerMotionMeleeAttackOneState::Exit(void) {
}