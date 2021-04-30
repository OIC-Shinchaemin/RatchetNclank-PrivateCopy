#include "PlayerActionJumpSetState.h"


state::PlayerActionJumpSetState::PlayerActionJumpSetState() :
    super(),
    _jump_com() {
}

state::PlayerActionJumpSetState::~PlayerActionJumpSetState() {
}

void state::PlayerActionJumpSetState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_jump_com = ptr->GetComponent<my::PlayerJumpSetComponent>();
}

const char* state::PlayerActionJumpSetState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpSetState.c_str();
}

void state::PlayerActionJumpSetState::Update(float delta_time) {
}

void state::PlayerActionJumpSetState::Enter(void) {
    if (auto jump_com = _jump_com.lock()) {
        jump_com->Start();
    } // if
}

void state::PlayerActionJumpSetState::Exit(void) {
    if (auto jump_com = _jump_com.lock()) {
        jump_com->End();
    } // if
}