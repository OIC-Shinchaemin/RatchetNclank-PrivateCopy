#include "PlayerMotionJumpUpState.h"


state::PlayerMotionJumpUpState::PlayerMotionJumpUpState() :
    super() {
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::PlayerMotionJumpUpState::~PlayerMotionJumpUpState() {
}

const char* state::PlayerMotionJumpUpState::GetName(void) const {
    return "PlayerMotionJumpUpState";
}

void state::PlayerMotionJumpUpState::Update(float delta_time) {
}

void state::PlayerMotionJumpUpState::Enter(void) {
    super::ChangeMotion(my::Player::MotionType::JumpUp);
}

void state::PlayerMotionJumpUpState::Exit(void) {
}