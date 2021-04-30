#include "PlayerMotionJumpDownState.h"


state::PlayerMotionJumpDownState::PlayerMotionJumpDownState() :
    super() {
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::PlayerMotionJumpDownState::~PlayerMotionJumpDownState() {
}

const char* state::PlayerMotionJumpDownState::GetName(void) const {
    return "PlayerMotionJumpDownState";
}

void state::PlayerMotionJumpDownState::Update(float delta_time) {
}

void state::PlayerMotionJumpDownState::Enter(void) {
    super::ChangeMotion(my::Player::MotionType::JumpDown);
}

void state::PlayerMotionJumpDownState::Exit(void) {
}