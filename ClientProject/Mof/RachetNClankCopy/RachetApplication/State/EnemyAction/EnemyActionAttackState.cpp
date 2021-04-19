#include "EnemyActionAttackState.h"


state::EnemyActionAttackState::EnemyActionAttackState() :
    super(),
    _attack_com() {
}

state::EnemyActionAttackState::~EnemyActionAttackState() {
}

const char* state::EnemyActionAttackState::GetName(void) const {
    return "EnemyActionAttackState";
}

void state::EnemyActionAttackState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_enemy_com = ptr->GetComponent<my::EnemyComponent>();
    this->_idle_com = ptr->GetComponent<my::EnemyIdleComponent>();
    this->_move_com = ptr->GetComponent<my::EnemyMoveComponent>();
    this->_attack_com = ptr->GetComponent<my::EnemyAttackComponent>();
}

void state::EnemyActionAttackState::Update(float delta_time) {
}

void state::EnemyActionAttackState::Enter(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->Start();
    } // if
    if (auto move_com = _move_com.lock()) {
        move_com->SetMoveSpeed(0.0f);
        move_com->SetAngularSpeed(0.0f);
    } // if
}

void state::EnemyActionAttackState::Exit(void) {
}