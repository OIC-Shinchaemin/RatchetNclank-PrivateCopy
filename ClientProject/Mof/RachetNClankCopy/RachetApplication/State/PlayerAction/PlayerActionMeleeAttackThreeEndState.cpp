#include "PlayerActionMeleeAttackThreeEndState.h"


state::PlayerActionMeleeAttackThreeEndState::PlayerActionMeleeAttackThreeEndState() :
    super(),
    _attack_com() {
}

state::PlayerActionMeleeAttackThreeEndState::~PlayerActionMeleeAttackThreeEndState() {
}

void state::PlayerActionMeleeAttackThreeEndState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_attack_com = ptr->GetComponent<my::PlayerMeleeAttackThreeEndComponent>();
}

const char* state::PlayerActionMeleeAttackThreeEndState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackThreeEndState.c_str();
}

void state::PlayerActionMeleeAttackThreeEndState::Update(float delta_time) {
}

void state::PlayerActionMeleeAttackThreeEndState::Enter(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->Start();
    } // if
}

void state::PlayerActionMeleeAttackThreeEndState::Exit(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->End();
    } // if
}