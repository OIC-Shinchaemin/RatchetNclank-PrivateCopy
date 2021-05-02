#include "PlayerActionMeleeAttackOneState.h"


state::PlayerActionMeleeAttackOneState::PlayerActionMeleeAttackOneState() :
    super(),
    _attack_com() {
}

state::PlayerActionMeleeAttackOneState::~PlayerActionMeleeAttackOneState() {
}

void state::PlayerActionMeleeAttackOneState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_attack_com = ptr->GetComponent<my::PlayerMeleeAttackOneComponent>();
}

const char* state::PlayerActionMeleeAttackOneState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackOneState.c_str();
}

void state::PlayerActionMeleeAttackOneState::Update(float delta_time) {
}

void state::PlayerActionMeleeAttackOneState::Enter(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->Start();
    } // if
}

void state::PlayerActionMeleeAttackOneState::Exit(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->End();
    } // if
}