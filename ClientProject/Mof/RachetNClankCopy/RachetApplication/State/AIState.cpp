#include "AIState.h"

#include "../Factory/FactoryManager.h"


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

void state::AIState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    this->_enemy = std::dynamic_pointer_cast<my::Enemy>(ptr);
}

void state::AIState::GenerateBehaviourExecutor(void) {
    _behaviour_executor = my::FactoryManager::Singleton().CreateBehaviourExecutor(_behaviour_path.c_str());
}

void state::AIState::Update(float delta_time) {
    if (auto enemy = this->GetEnemy(); enemy) {
        _behaviour_executor->Execute(enemy);
    } // if
}

void state::AIState::Enter(void) {
    _behaviour_executor->Reset();
}

void state::AIState::Exit(void) {
    //_behaviour_executor->Reset();
}

void state::AIState::DebugRender(void) {
    _behaviour_executor->DebugRender();
}