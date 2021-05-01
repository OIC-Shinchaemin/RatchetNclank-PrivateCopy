#include "PlayerActionDoubleJumpState.h"


state::PlayerActionDoubleJumpState::PlayerActionDoubleJumpState() :
    super(),
    _jump_com() {
}

state::PlayerActionDoubleJumpState::~PlayerActionDoubleJumpState() {
}

void state::PlayerActionDoubleJumpState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_jump_com = ptr->GetComponent<my::PlayerDoubleJumpComponent>();
}

const char* state::PlayerActionDoubleJumpState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionDoubleJumpState.c_str();
}

void state::PlayerActionDoubleJumpState::Update(float delta_time) {
}

void state::PlayerActionDoubleJumpState::Enter(void) {
    if (auto jump_com = _jump_com.lock()) {
        jump_com->Start();
    } // if
}

void state::PlayerActionDoubleJumpState::Exit(void) {
    if (auto jump_com = _jump_com.lock()) {
        jump_com->End();
    } // if
}