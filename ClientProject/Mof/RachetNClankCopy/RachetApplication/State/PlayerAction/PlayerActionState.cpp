#include "PlayerActionState.h"


std::shared_ptr<my::Actor> state::PlayerActionState::GetActor(void) const {
    return this->_actor.lock();
}

bool state::PlayerActionState::ChangeState(const char* next) const {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(next);
        return true;
    } // if
    return false;
}

state::PlayerActionState::PlayerActionState() :
    _actor(),
    _state_com() {
}

state::PlayerActionState::~PlayerActionState() {
}

void state::PlayerActionState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    _actor = ptr;
    _state_com = ptr->GetComponent<my::PlayerStateComponent>();
}