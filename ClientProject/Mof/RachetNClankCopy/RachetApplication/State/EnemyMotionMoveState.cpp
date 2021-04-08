#include "EnemyMotionMoveState.h"


state::EnemyMotionMoveState::EnemyMotionMoveState() :
    super() {
    super::_motion_same = false;
}

state::EnemyMotionMoveState::~EnemyMotionMoveState() {
}

const char* state::EnemyMotionMoveState::GetName(void) const {
    return "EnemyMotionMoveState";
}

void state::EnemyMotionMoveState::Update(float delta_time) {
}

void state::EnemyMotionMoveState::Enter(void) {
    super::ChangeMotion(my::Enemy::MotionType::MoveRun);
}

void state::EnemyMotionMoveState::Exit(void) {
}