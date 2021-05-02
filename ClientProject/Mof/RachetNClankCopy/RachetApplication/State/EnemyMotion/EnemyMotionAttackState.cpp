#include "EnemyMotionAttackState.h"


state::EnemyMotionAttackState::EnemyMotionAttackState() :
    super() {
    super::_motion_speed = 0.5f;
    super::_motion_loop = false;
}

state::EnemyMotionAttackState::~EnemyMotionAttackState() {
}

void state::EnemyMotionAttackState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
}

const char* state::EnemyMotionAttackState::GetName(void) const {
    return "EnemyMotionAttackState";
}

void state::EnemyMotionAttackState::Update(float delta_time) {
}

void state::EnemyMotionAttackState::Enter(void) {
    super::ChangeMotion(my::Enemy::MotionType::AttackOne);
}

void state::EnemyMotionAttackState::Exit(void) {
}