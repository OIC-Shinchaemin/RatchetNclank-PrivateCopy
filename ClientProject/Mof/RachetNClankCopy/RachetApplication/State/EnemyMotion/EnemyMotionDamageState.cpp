#include "EnemyMotionDamageState.h"


state::EnemyMotionDamageState::EnemyMotionDamageState() :
    super() {
    super::_motion_speed = 1.0f;
    super::_motion_loop = false;
    super::_motion_same = false;
}

state::EnemyMotionDamageState::~EnemyMotionDamageState() {
}

const char* state::EnemyMotionDamageState::GetName(void) const {
    return "EnemyMotionDamageState";
}

void state::EnemyMotionDamageState::Update(float delta_time) {
}

void state::EnemyMotionDamageState::Enter(void) {
    super::ChangeMotion(my::Enemy::MotionType::Damage);
}

void state::EnemyMotionDamageState::Exit(void) {
}