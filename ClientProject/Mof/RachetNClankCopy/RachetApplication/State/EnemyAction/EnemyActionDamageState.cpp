#include "EnemyActionDamageState.h"


state::EnemyActionDamageState::EnemyActionDamageState() :
    super(),
    _damage_com(),
    _move_com(){
}

state::EnemyActionDamageState::~EnemyActionDamageState() {
}

void state::EnemyActionDamageState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_damage_com = ptr->GetComponent<my::EnemyDamageComponent>();
    this->_move_com = ptr->GetComponent<my::EnemyMoveComponent>();
}

const char* state::EnemyActionDamageState::GetName(void) const {
    return state::EnemyActionStateType::kEnemyActionDamageState.c_str();
}

void state::EnemyActionDamageState::Update(float delta_time) {
}

void state::EnemyActionDamageState::Enter(void) {
    if (auto damage_com = _damage_com.lock()) {
        damage_com->Start();
    } // if
}

void state::EnemyActionDamageState::Exit(void) {
    if (auto damage_com = _damage_com.lock()) {
        damage_com->End();
    } // if
}