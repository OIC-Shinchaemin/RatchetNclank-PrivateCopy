#include "ActionState.h"


state::ActionState::ActionState() :
    _action_com() {
}

state::ActionState::~ActionState() {
}

void state::ActionState::SetActionComponent(const std::shared_ptr<my::ActionComponent>& ptr) {
    _action_com = ptr;
}

const char* state::ActionState::GetName(void) const {
    if (auto action_com = _action_com.lock()) {
        return action_com->GetStateType().data();
    } // if
    return nullptr;
}

void state::ActionState::Update(float delta_time) {

}

void state::ActionState::Enter(void) {
    if (auto action_com = _action_com.lock()) {
        action_com->Start();
    } // if
}

void state::ActionState::Exit(void) {
    if (auto action_com = _action_com.lock()) {
        action_com->End();
    } // if
}