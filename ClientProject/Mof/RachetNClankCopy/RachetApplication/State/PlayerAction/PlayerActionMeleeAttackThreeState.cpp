#include "PlayerActionMeleeAttackThreeState.h"


state::PlayerActionMeleeAttackThreeState::PlayerActionMeleeAttackThreeState() :
    super(),
    _attack_com() {
}

state::PlayerActionMeleeAttackThreeState::~PlayerActionMeleeAttackThreeState() {
}

void state::PlayerActionMeleeAttackThreeState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_attack_com = ptr->GetComponent<my::PlayerMeleeAttackThreeComponent>();
}

const char* state::PlayerActionMeleeAttackThreeState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackThreeState.c_str();
}

void state::PlayerActionMeleeAttackThreeState::Update(float delta_time) {
}

void state::PlayerActionMeleeAttackThreeState::Enter(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->Start();
    } // if
}

void state::PlayerActionMeleeAttackThreeState::Exit(void) {
    if (auto attack_com = _attack_com.lock()) {
        attack_com->End();
    } // if
}