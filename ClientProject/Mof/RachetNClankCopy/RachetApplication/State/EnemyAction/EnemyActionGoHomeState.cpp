#include "EnemyActionGoHomeState.h"


state::EnemyActionGoHomeState::EnemyActionGoHomeState() :
    super() {
}

state::EnemyActionGoHomeState::~EnemyActionGoHomeState() {
}

void state::EnemyActionGoHomeState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_move_com = ptr->GetComponent<my::EnemyGoHomeComponent>();
}

const char* state::EnemyActionGoHomeState::GetName(void) const {
    return "EnemyActionGoHomeState";
}

void state::EnemyActionGoHomeState::Update(float delta_time) {
}

void state::EnemyActionGoHomeState::Enter(void) {
    if (auto move_com = _move_com.lock()) {
        move_com->Start();
    } // if
}

void state::EnemyActionGoHomeState::Exit(void) {
    if (auto move_com = _move_com.lock()) {
        move_com->End();
    } // if
}