#include "PlayerMotionDeadState.h"


state::PlayerMotionDeadState::PlayerMotionDeadState() :
    super() {
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::PlayerMotionDeadState::~PlayerMotionDeadState() {
}

const char* state::PlayerMotionDeadState::GetName(void) const {
    return state::PlayerMotionStateType::kPlayerMotionDeadState.c_str();
}

void state::PlayerMotionDeadState::Update(float delta_time) {
}

void state::PlayerMotionDeadState::Enter(void) {
    super::ChangeMotion(my::Player::MotionType::DamageDead);
}

void state::PlayerMotionDeadState::Exit(void) {
}