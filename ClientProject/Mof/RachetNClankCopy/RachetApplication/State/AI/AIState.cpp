#include "AIState.h"

#include "../../Factory/FactoryManager.h"


std::shared_ptr<my::Actor> state::AIState::GetActor(void) const {
    if (auto actor = _actor.lock()) {
        return actor;
    } // if
    return nullptr;
}

state::AIState::AIState() :
    _actor(),
    _behaviour_executor() {
}

state::AIState::~AIState() {
}

void state::AIState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    this->_actor = ptr;
}

void state::AIState::GenerateBehaviourExecutor(const std::string& path) {
    _behaviour_executor = my::FactoryManager::Singleton().CreateBehaviourExecutor(path.c_str());
    _behaviour_executor->Prepare(_actor.lock());
}

void state::AIState::Update(float delta_time) {
    if (auto actor = this->GetActor(); actor) {
        _behaviour_executor->Execute();
    } // if
}

void state::AIState::Enter(void) {
    _behaviour_executor->Reset();
}

void state::AIState::Exit(void) {
}

void state::AIState::DebugRender(void) {
    _behaviour_executor->DebugRender();
}