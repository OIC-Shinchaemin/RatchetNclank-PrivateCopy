#include "PlayerActionMoveState.h"


state::PlayerActionMoveState::PlayerActionMoveState() :
    super(),
    _move_com() {
}

state::PlayerActionMoveState::~PlayerActionMoveState() {
}

void state::PlayerActionMoveState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_move_com = ptr->GetComponent<my::PlayerMoveComponent>();
}

const char* state::PlayerActionMoveState::GetName(void) const {
    return "PlayerActionMoveState";
}

void state::PlayerActionMoveState::Update(float delta_time) {
}

void state::PlayerActionMoveState::Enter(void) {
    if (auto move_com = _move_com.lock()) {
        move_com->Start();
    } // if
}

void state::PlayerActionMoveState::Exit(void) {
    if (auto move_com = _move_com.lock()) {
        move_com->End();
    } // if
}