#include "PlayerActionMeleeAttackTwoState.h"


state::PlayerActionMeleeAttackTwoState::PlayerActionMeleeAttackTwoState() :
    super(),
    _attack_com() {
}

state::PlayerActionMeleeAttackTwoState::~PlayerActionMeleeAttackTwoState() {
}

void state::PlayerActionMeleeAttackTwoState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_attack_com = ptr->GetComponent<my::PlayerMeleeAttackTwoComponent>();
}

const char* state::PlayerActionMeleeAttackTwoState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackTwoState.c_str();
}

void state::PlayerActionMeleeAttackTwoState::Update(float delta_time) {
}

void state::PlayerActionMeleeAttackTwoState::Enter(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->Start();
    } // if
}

void state::PlayerActionMeleeAttackTwoState::Exit(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->End();
    } // if
}