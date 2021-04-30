#include "PlayerMotionJumpLandingState.h"


state::PlayerMotionJumpLandingState::PlayerMotionJumpLandingState() :
    super() {
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::PlayerMotionJumpLandingState::~PlayerMotionJumpLandingState() {
}

const char* state::PlayerMotionJumpLandingState::GetName(void) const {
    return "PlayerMotionJumpLandingState";
}

void state::PlayerMotionJumpLandingState::Update(float delta_time) {
}

void state::PlayerMotionJumpLandingState::Enter(void) {
    super::ChangeMotion(my::Player::MotionType::JumpLanding);
}

void state::PlayerMotionJumpLandingState::Exit(void) {
}