#include "PlayerMotionMoveState.h"


state::PlayerMotionMoveState::PlayerMotionMoveState() :
    super() {
    super::_motion_same = false;
}

state::PlayerMotionMoveState::~PlayerMotionMoveState() {
}

const char* state::PlayerMotionMoveState::GetName(void) const {
    return "PlayerMotionMoveState";
}

void state::PlayerMotionMoveState::Update(float delta_time) {
}

void state::PlayerMotionMoveState::Enter(void) {
    super::ChangeMotion(Player::MotionType::MoveRun);
}

void state::PlayerMotionMoveState::Exit(void) {
}