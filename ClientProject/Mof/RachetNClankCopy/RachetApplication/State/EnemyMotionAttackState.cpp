#include "EnemyMotionAttackState.h"


state::EnemyMotionAttackState::EnemyMotionAttackState() :
    super() {
    super::_motion_loop = false;
}

state::EnemyMotionAttackState::~EnemyMotionAttackState() {
}

const char* state::EnemyMotionAttackState::GetName(void) const {
    return "EnemyMotionAttackState";
}

void state::EnemyMotionAttackState::Update(float delta_time) {
    auto v = super::_velocity->GetVelocity();
    auto length = Mof::CVector2(v.x, v.z).Length();    
    if (0.0001f < length) { // move component is active
        super::ChangeState("EnemyMotionMoveState");
    } // if
}

void state::EnemyMotionAttackState::Enter(void) {
    super::ChangeMotion(my::Enemy::MotionType::AttackOne);
}

void state::EnemyMotionAttackState::Exit(void) {
}