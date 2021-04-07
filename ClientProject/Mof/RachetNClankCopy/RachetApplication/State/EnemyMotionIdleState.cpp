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
    auto v = super::_velocity->GetVelocity();
    auto length = Mof::CVector2(v.x, v.z).Length();    
    if (0.0001f < length) { // move component is active
        //super::ChangeState("EnemyMotionMoveState");
    } // if
}

void state::EnemyMotionIdleState::Enter(void) {
    super::ChangeMotion(my::Enemy::MotionType::IdleWait);
}

void state::EnemyMotionIdleState::Exit(void) {
}