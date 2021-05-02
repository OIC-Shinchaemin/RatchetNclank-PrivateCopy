#include "PlayerActionJumpDownState.h"


state::PlayerActionJumpDownState::PlayerActionJumpDownState() :
    super(),
    _jump_com() {
}

state::PlayerActionJumpDownState::~PlayerActionJumpDownState() {
}

void state::PlayerActionJumpDownState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_jump_com = ptr->GetComponent<my::PlayerJumpDownComponent>();
}

const char* state::PlayerActionJumpDownState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpDownState.c_str();
}

void state::PlayerActionJumpDownState::Update(float delta_time) {
}

void state::PlayerActionJumpDownState::Enter(void) {
    if (auto jump_com = _jump_com.lock()) {
        jump_com->Start();
    } // if
}

void state::PlayerActionJumpDownState::Exit(void) {
    if (auto jump_com = _jump_com.lock()) {
        jump_com->End();
    } // if
}