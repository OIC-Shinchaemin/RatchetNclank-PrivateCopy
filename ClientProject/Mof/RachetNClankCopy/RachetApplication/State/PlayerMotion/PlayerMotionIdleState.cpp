#include "PlayerMotionIdleState.h"


state::PlayerMotionIdleState::PlayerMotionIdleState() :
    super() {
    super::_motion_loop = true;
    super::_motion_same = false;
}

state::PlayerMotionIdleState::~PlayerMotionIdleState() {
}

const char* state::PlayerMotionIdleState::GetName(void) const {
    return "PlayerMotionIdleState";
}

void state::PlayerMotionIdleState::Update(float delta_time) {
}

void state::PlayerMotionIdleState::Enter(void) {
    super::ChangeMotion(my::Player::MotionType::IdleWait);
}

void state::PlayerMotionIdleState::Exit(void) {
}