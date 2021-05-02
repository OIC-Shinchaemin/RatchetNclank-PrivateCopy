#include "PlayerActionDamageState.h"


state::PlayerActionDamageState::PlayerActionDamageState() :
    super(),
    _damage_com(){
}

state::PlayerActionDamageState::~PlayerActionDamageState() {
}

void state::PlayerActionDamageState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_damage_com = ptr->GetComponent<my::PlayerDamageComponent>();
}

const char* state::PlayerActionDamageState::GetName(void) const {
    return state::PlayerActionStateType::kPlayerActionDamageState.c_str();
}

void state::PlayerActionDamageState::Update(float delta_time) {
}

void state::PlayerActionDamageState::Enter(void) {
    if (auto damage_com = _damage_com.lock()) {
        damage_com->Start();
    } // if
}

void state::PlayerActionDamageState::Exit(void) {
    if (auto damage_com = _damage_com.lock()) {
        damage_com->End();
    } // if
}