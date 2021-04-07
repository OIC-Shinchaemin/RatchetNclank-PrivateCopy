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
    auto v = super::_velocity->GetVelocity();
    auto length = Mof::CVector2(v.x, v.z).Length();
    if (0.0001f >= length) { // move component is inactive
        super::ChangeState("EnemyMotionIdleState");
    } // if

    if (auto attack = super::_attack.lock(); !super::_attack.expired() && attack->IsActive()) {
        //super::ChangeState("EnemyMotionAttackState");
    } // if
}

void state::EnemyMotionMoveState::Enter(void) {
    super::ChangeMotion(my::Enemy::MotionType::MoveRun);
}

void state::EnemyMotionMoveState::Exit(void) {
}