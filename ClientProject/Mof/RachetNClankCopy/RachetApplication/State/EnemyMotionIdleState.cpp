#include "EnemyMotionIdleState.h"


state::EnemyMotionIdleState::EnemyMotionIdleState() :
    super() {
    super::_motion_loop = true;
    super::_motion_same = false;
}

state::EnemyMotionIdleState::~EnemyMotionIdleState() {
}

const char* state::EnemyMotionIdleState::GetName(void) const {
    return "EnemyMotionIdleState";
}

void state::EnemyMotionIdleState::Update(float delta_time) {
}

void state::EnemyMotionIdleState::Enter(void) {
    super::ChangeMotion(my::Enemy::MotionType::IdleWait);
}

void state::EnemyMotionIdleState::Exit(void) {
}