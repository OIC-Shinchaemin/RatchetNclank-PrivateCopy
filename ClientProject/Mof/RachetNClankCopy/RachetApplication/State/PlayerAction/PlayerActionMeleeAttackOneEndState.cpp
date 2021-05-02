#include "PlayerActionMeleeAttackOneEndState.h"


state::PlayerActionMeleeAttackOneEndState::PlayerActionMeleeAttackOneEndState() :
    super(),
    _attack_com() {
}

state::PlayerActionMeleeAttackOneEndState::~PlayerActionMeleeAttackOneEndState() {
}

void state::PlayerActionMeleeAttackOneEndState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_attack_com = ptr->GetComponent<my::PlayerMeleeAttackOneEndComponent>();
}

const char* state::PlayerActionMeleeAttackOneEndState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackOneEndState.c_str();
}

void state::PlayerActionMeleeAttackOneEndState::Update(float delta_time) {
}

void state::PlayerActionMeleeAttackOneEndState::Enter(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->Start();
    } // if
}

void state::PlayerActionMeleeAttackOneEndState::Exit(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->End();
    } // if
}