#include "AIState.h"


std::shared_ptr<my::Enemy> state::AIState::GetEnemy(void) const {
    if (auto enemy = _enemy.lock()) {
        return enemy;
    } // if
    return nullptr;
}

state::AIState::AIState() :
    _enemy(),
    _behaviour_executor(),
    _behaviour_path() {
}

state::AIState::~AIState() {
}

void state::AIState::SetEnemy(const std::shared_ptr<my::Enemy>& ptr) {
    this->_enemy = ptr;
}

void state::AIState::GenerateBehaviourExecutor(const my::BehaviourExecutorFactory& ptr) {
    _behaviour_executor = ptr.Create(_behaviour_path.c_str());
}

void state::AIState::Update(float delta_time) {
    if (auto enemy = this->GetEnemy(); enemy) {
        _behaviour_executor->Execute(enemy);
    } // if
}

void state::AIState::Enter(void) {
}

void state::AIState::Exit(void) {
    _behaviour_executor->Reset();
}