#include "EnemyActionIdleState.h"


state::EnemyActionIdleState::EnemyActionIdleState() :
    super(),
    _idle_com() {
}

state::EnemyActionIdleState::~EnemyActionIdleState() {
}

void state::EnemyActionIdleState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_idle_com = ptr->GetComponent<my::EnemyIdleComponent>();
    this->_move_com = ptr->GetComponent<my::EnemyMoveComponent>();
    this->_attack_com = ptr->GetComponent<my::EnemyAttackComponent>();

}

const char* state::EnemyActionIdleState::GetName(void) const {
    return "EnemyActionIdleState";
}

void state::EnemyActionIdleState::Update(float delta_time) {
}

void state::EnemyActionIdleState::Enter(void) {
    if (auto idle_com = _idle_com.lock()) {
        idle_com->Start();
    } // if
}

void state::EnemyActionIdleState::Exit(void) {
}