#include "PlayerActionDeadState.h"


state::PlayerActionDeadState::PlayerActionDeadState() :
    super(),
    _dead_com(){
}

state::PlayerActionDeadState::~PlayerActionDeadState() {
}

void state::PlayerActionDeadState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_dead_com = ptr->GetComponent<my::PlayerDeadComponent>();
}

const char* state::PlayerActionDeadState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionDeadState.c_str();
}

void state::PlayerActionDeadState::Update(float delta_time) {
}

void state::PlayerActionDeadState::Enter(void) {
    if (auto dead_com = _dead_com.lock()) {
        dead_com->Start();
    } // if
}

void state::PlayerActionDeadState::Exit(void) {
    if (auto dead_com = _dead_com.lock()) {
        dead_com->End();
    } // if
}