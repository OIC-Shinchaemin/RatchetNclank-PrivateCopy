#include "EnemyActionMoveState.h"


state::EnemyActionMoveState::EnemyActionMoveState() :
    super() {
}

state::EnemyActionMoveState::~EnemyActionMoveState() {
}

void state::EnemyActionMoveState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_move_com = ptr->GetComponent<my::EnemyMoveComponent>();
}

const char* state::EnemyActionMoveState::GetName(void) const {
    return "EnemyActionMoveState";
}

void state::EnemyActionMoveState::Update(float delta_time) {
}

void state::EnemyActionMoveState::Enter(void) {
    if (auto move_com = _move_com.lock()) {
        move_com->Start();
    } // if
}

void state::EnemyActionMoveState::Exit(void) {
    if (auto move_com = _move_com.lock()) {
        move_com->End();
    } // if
}