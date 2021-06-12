#include "ActionState.h"


ratchet::state::ActionState::ActionState() :
    _action_com() {
}

ratchet::state::ActionState::~ActionState() {
}

void ratchet::state::ActionState::SetActionComponent(const std::shared_ptr<ratchet::component::ActionComponent>& ptr) {
    _action_com = ptr;
}

const char* ratchet::state::ActionState::GetName(void) const {
    if (auto action_com = _action_com.lock()) {
        return action_com->GetStateType().data();
    } // if
    return nullptr;
}

void ratchet::state::ActionState::Update(float delta_time) {
}

void ratchet::state::ActionState::Enter(void) {
    if (auto action_com = _action_com.lock()) {
        action_com->Start();
    } // if
}

void ratchet::state::ActionState::Exit(void) {
    if (auto action_com = _action_com.lock()) {
        action_com->End();
    } // if
}