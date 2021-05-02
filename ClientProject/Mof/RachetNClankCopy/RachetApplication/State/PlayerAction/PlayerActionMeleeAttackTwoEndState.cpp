#include "PlayerActionMeleeAttackTwoEndState.h"


state::PlayerActionMeleeAttackTwoEndState::PlayerActionMeleeAttackTwoEndState() :
    super(),
    _attack_com() {
}

state::PlayerActionMeleeAttackTwoEndState::~PlayerActionMeleeAttackTwoEndState() {
}

void state::PlayerActionMeleeAttackTwoEndState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_attack_com = ptr->GetComponent<my::PlayerMeleeAttackTwoEndComponent>();
}

const char* state::PlayerActionMeleeAttackTwoEndState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackTwoEndState.c_str();
}

void state::PlayerActionMeleeAttackTwoEndState::Update(float delta_time) {
}

void state::PlayerActionMeleeAttackTwoEndState::Enter(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->Start();
    } // if
}

void state::PlayerActionMeleeAttackTwoEndState::Exit(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->End();
    } // if
}