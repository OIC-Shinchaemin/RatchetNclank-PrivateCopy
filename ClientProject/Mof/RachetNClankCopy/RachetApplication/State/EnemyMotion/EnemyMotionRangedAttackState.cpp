#include "EnemyMotionRangedAttackState.h"


state::EnemyMotionRangedAttackState::EnemyMotionRangedAttackState() :
    super() {
    super::_motion_speed = 3.0f;
    super::_motion_loop = false;
}

state::EnemyMotionRangedAttackState ::~EnemyMotionRangedAttackState() {
}

void state::EnemyMotionRangedAttackState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
}

const char* state::EnemyMotionRangedAttackState::GetName(void) const {
    return "EnemyMotionRangedAttackState";
}

void state::EnemyMotionRangedAttackState::Update(float delta_time) {
}

void state::EnemyMotionRangedAttackState::Enter(void) {
    super::ChangeMotion(my::Enemy::MotionType::AttackOne);
}

void state::EnemyMotionRangedAttackState::Exit(void) {
}