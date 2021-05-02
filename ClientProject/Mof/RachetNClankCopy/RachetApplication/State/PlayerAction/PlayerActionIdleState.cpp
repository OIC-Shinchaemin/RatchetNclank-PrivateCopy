#include "PlayerActionIdleState.h"


state::PlayerActionIdleState::PlayerActionIdleState() :
    super(),
    _idle_com(){
}

state::PlayerActionIdleState::~PlayerActionIdleState() {
}

void state::PlayerActionIdleState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_idle_com = ptr->GetComponent<my::PlayerIdleComponent>();
}

const char* state::PlayerActionIdleState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionIdleState.c_str();
}

void state::PlayerActionIdleState::Update(float delta_time) {
}

void state::PlayerActionIdleState::Enter(void) {
    if (auto idle_com = _idle_com.lock()) {
        idle_com->Start();
    } // if
}

void state::PlayerActionIdleState::Exit(void) {
    if (auto idle_com = _idle_com.lock()) {
        idle_com->End();
    } // if
}