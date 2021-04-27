#include "EnemyActionMeleeAttackState.h"


state::EnemyActionMeleeAttackState::EnemyActionMeleeAttackState() :
    super(),
    _attack_com() {
}

state::EnemyActionMeleeAttackState::~EnemyActionMeleeAttackState() {
}

const char* state::EnemyActionMeleeAttackState::GetName(void) const {
    return "EnemyActionMeleeAttackState";
}

void state::EnemyActionMeleeAttackState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_enemy_com = ptr->GetComponent<my::EnemyComponent>();
    this->_idle_com = ptr->GetComponent<my::EnemyIdleComponent>();
    this->_move_com = ptr->GetComponent<my::EnemyMoveComponent>();
    this->_attack_com = ptr->GetComponent<my::EnemyMeleeAttackComponent>();
}

void state::EnemyActionMeleeAttackState::Update(float delta_time) {
}

void state::EnemyActionMeleeAttackState::Enter(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->Start();
    } // if
    if (auto move_com = _move_com.lock()) {
        move_com->SetMoveSpeed(0.0f);
        move_com->SetAngularSpeed(0.0f);
    } // if
    if (auto idle_com = _idle_com.lock()) {
        idle_com->SetAngularSpeed(0.0f);
    } // if
}

void state::EnemyActionMeleeAttackState::Exit(void) {
}