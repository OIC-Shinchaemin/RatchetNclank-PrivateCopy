#include "EnemyActionState.h"


bool state::EnemyActionState::ChangeState(const char* next) const {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(next);
        return true;
    } // if
    return false;
}

state::EnemyActionState::EnemyActionState() {
}

state::EnemyActionState::~EnemyActionState() {
}

void state::EnemyActionState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    _state_com = ptr->GetComponent<my::EnemyStateComponent>();
}