#include "EnemyMotionState.h"


bool state::EnemyMotionState::IsEndMotion(void) const {
    return _motion->IsEndMotion();
}

state::EnemyMotionState::EnemyMotionState() :
    _motion_speed(1.0f),
    _motion_loop(true),
    _motion_same(true),
    _motion(),
    _motion_names(),
    _enemy(),
    _velocity(),
    _attack() {
}

state::EnemyMotionState::~EnemyMotionState() {
}

void state::EnemyMotionState::SetLPMeshMotionController(Mof::LPMeshMotionController ptr) {
    this->_motion = ptr;
}

void state::EnemyMotionState::SetMotionNames(const std::weak_ptr<my::MotionNames>& ptr) {
    _motion_names = ptr;
}

void state::EnemyMotionState::SetEnemy(const std::shared_ptr<my::Enemy>& ptr) {
    _enemy = ptr;
}

void state::EnemyMotionState::SetVelocity(my::Velocity* ptr) {
    this->_velocity = ptr;
}

void state::EnemyMotionState::SetAttack(const std::shared_ptr<my::Attack>& ptr) {
    this->_attack = ptr;
}