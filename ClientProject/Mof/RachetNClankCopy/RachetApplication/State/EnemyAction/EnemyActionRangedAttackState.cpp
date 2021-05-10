#include "EnemyActionRangedAttackState.h"


state::EnemyActionRangedAttackState::EnemyActionRangedAttackState() :
    super(),
    _attack_com() {
}

state::EnemyActionRangedAttackState::~EnemyActionRangedAttackState() {
}

const char* state::EnemyActionRangedAttackState::GetName(void) const {
    return "EnemyActionRangedAttackState";
}

void state::EnemyActionRangedAttackState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_attack_com = ptr->GetComponent<my::EnemyRangedAttackComponent>();
}

void state::EnemyActionRangedAttackState::Update(float delta_time) {
}

void state::EnemyActionRangedAttackState::Enter(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->Start();
    } // if
}

void state::EnemyActionRangedAttackState::Exit(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->End();
    } // if
}