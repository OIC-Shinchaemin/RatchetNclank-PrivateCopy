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
    this->_attack_com = ptr->GetComponent<my::EnemyMeleeAttackComponent>();
}

void state::EnemyActionMeleeAttackState::Update(float delta_time) {
}

void state::EnemyActionMeleeAttackState::Enter(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->Start();
    } // if
}

void state::EnemyActionMeleeAttackState::Exit(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->End();
    } // if
}