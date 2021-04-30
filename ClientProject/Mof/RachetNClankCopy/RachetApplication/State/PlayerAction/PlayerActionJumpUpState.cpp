#include "PlayerActionJumpUpState.h"


state::PlayerActionJumpUpState::PlayerActionJumpUpState() :
    super(),
    _jump_com() {
}

state::PlayerActionJumpUpState::~PlayerActionJumpUpState() {
}

void state::PlayerActionJumpUpState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_jump_com = ptr->GetComponent<my::PlayerJumpUpComponent>();
}

const char* state::PlayerActionJumpUpState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpUpState.c_str();
}

void state::PlayerActionJumpUpState::Update(float delta_time) {
}

void state::PlayerActionJumpUpState::Enter(void) {
    if (auto jump_com = _jump_com.lock()) {
        jump_com->Start();
    } // if
}

void state::PlayerActionJumpUpState::Exit(void) {
    if (auto jump_com = _jump_com.lock()) {
        jump_com->End();
    } // if
}