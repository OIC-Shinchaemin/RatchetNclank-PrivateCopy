#include "EnemyActionState.h"


std::shared_ptr<my::Actor> state::EnemyActionState::GetActor(void) const {
    return this->_actor.lock();
}

bool state::EnemyActionState::ChangeState(const char* next) const {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(next);
        return true;
    } // if
    return false;
}

state::EnemyActionState::EnemyActionState() :
    _actor(),
    _state_com() {
}

state::EnemyActionState::~EnemyActionState() {
}

void state::EnemyActionState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    _actor = ptr;
    _state_com = ptr->GetComponent<my::EnemyStateComponent>();
}