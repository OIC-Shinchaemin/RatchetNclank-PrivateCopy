#include "PlayerMotionJumpSetState.h"


state::PlayerMotionJumpSetState::PlayerMotionJumpSetState() :
    super() {
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::PlayerMotionJumpSetState::~PlayerMotionJumpSetState() {
}

const char* state::PlayerMotionJumpSetState::GetName(void) const {
    return state::PlayerMotionStateType::kPlayerMotionJumpSetState.c_str();
}

void state::PlayerMotionJumpSetState::Update(float delta_time) {
}

void state::PlayerMotionJumpSetState::Enter(void) {
    super::ChangeMotion(my::Player::MotionType::JumpSet);
}

void state::PlayerMotionJumpSetState::Exit(void) {
}