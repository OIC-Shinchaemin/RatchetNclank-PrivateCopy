#include "PlayerMotionDoubleJumpState.h"


state::PlayerMotionDoubleJumpState::PlayerMotionDoubleJumpState() :
    super() {
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::PlayerMotionDoubleJumpState::~PlayerMotionDoubleJumpState() {
}

const char* state::PlayerMotionDoubleJumpState::GetName(void) const {
    return state::PlayerMotionStateType::kPlayerMotionDoubleJumpState.c_str();
}

void state::PlayerMotionDoubleJumpState::Update(float delta_time) {
}

void state::PlayerMotionDoubleJumpState::Enter(void) {
    super::ChangeMotion(my::Player::MotionType::DoubleJump);
}

void state::PlayerMotionDoubleJumpState::Exit(void) {
}