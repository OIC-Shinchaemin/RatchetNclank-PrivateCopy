#include "PlayerMotionMeleeAttackThreeState.h"


state::PlayerMotionMeleeAttackThreeState::PlayerMotionMeleeAttackThreeState() :
    super() {
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::PlayerMotionMeleeAttackThreeState::~PlayerMotionMeleeAttackThreeState() {
}

const char* state::PlayerMotionMeleeAttackThreeState::GetName(void) const {
    return state::PlayerMotionStateType::kPlayerMotionMeleeAttackThreeState.c_str();
}

void state::PlayerMotionMeleeAttackThreeState::Update(float delta_time) {
}

void state::PlayerMotionMeleeAttackThreeState::Enter(void) {
    super::ChangeMotion(my::Player::MotionType::MeleeAttackThree);
}

void state::PlayerMotionMeleeAttackThreeState::Exit(void) {
}