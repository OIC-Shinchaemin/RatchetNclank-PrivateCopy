#include "PlayerActionJumpState.h"


state::PlayerActionJumpState::PlayerActionJumpState() :
    super(),
    _jump_com() {
}

state::PlayerActionJumpState::~PlayerActionJumpState() {
}

void state::PlayerActionJumpState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_jump_com = ptr->GetComponent<my::PlayerJumpComponent>();
}

const char* state::PlayerActionJumpState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpState.c_str();
}

void state::PlayerActionJumpState::Update(float delta_time) {
}

void state::PlayerActionJumpState::Enter(void) {
    if (auto jump_com = _jump_com.lock()) {
        jump_com->Start();
    } // if
}

void state::PlayerActionJumpState::Exit(void) {
    if (auto jump_com = _jump_com.lock()) {
        jump_com->End();
    } // if
}