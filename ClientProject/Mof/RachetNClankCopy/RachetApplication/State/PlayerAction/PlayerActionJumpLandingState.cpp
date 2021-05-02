#include "PlayerActionJumpLandingState.h"


state::PlayerActionJumpLandingState::PlayerActionJumpLandingState() :
    super(),
    _jump_com() {
}

state::PlayerActionJumpLandingState::~PlayerActionJumpLandingState() {
}

void state::PlayerActionJumpLandingState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_jump_com = ptr->GetComponent<my::PlayerJumpLandingComponent>();
}

const char* state::PlayerActionJumpLandingState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpLandingState.c_str();
}

void state::PlayerActionJumpLandingState::Update(float delta_time) {
}

void state::PlayerActionJumpLandingState::Enter(void) {
    if (auto jump_com = _jump_com.lock()) {
        jump_com->Start();
    } // if
}

void state::PlayerActionJumpLandingState::Exit(void) {
    if (auto jump_com = _jump_com.lock()) {
        jump_com->End();
    } // if
}