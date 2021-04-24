#include "EnemyMotionAttackState.h"


state::EnemyMotionAttackState::EnemyMotionAttackState() :
    super(),
    _attack_com() {
    super::_motion_speed = 0.5f;
    super::_motion_loop = false;
}

state::EnemyMotionAttackState::~EnemyMotionAttackState() {
}

void state::EnemyMotionAttackState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    _attack_com = ptr->GetComponent<my::EnemyMeleeAttackComponent>();
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
    if (auto attack_com = _attack_com.lock()) {
    } // if
}