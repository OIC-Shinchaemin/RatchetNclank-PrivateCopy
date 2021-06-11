#include "AIState.h"

#include "../../Factory/FactoryManager.h"


std::shared_ptr<ratchet::actor::Actor> ratchet::state::ai::AIState::GetActor(void) const {
    if (auto actor = _actor.lock()) {
        return actor;
    } // if
    return nullptr;
}

ratchet::state::ai::AIState::AIState() :
    _actor(),
    _behaviour_executor() {
}

ratchet::state::ai::AIState::~AIState() {
}

void ratchet::state::ai::AIState::SetActor(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    this->_actor = ptr;
}

void ratchet::state::ai::AIState::GenerateBehaviourExecutor(const std::string& path) {
    _behaviour_executor = ratchet::factory::FactoryManager::Singleton().CreateBehaviourExecutor(path.c_str());
    _behaviour_executor->Prepare(_actor.lock());
}

void ratchet::state::ai::AIState::Update(float delta_time) {
    if (auto actor = this->GetActor(); actor) {
        _behaviour_executor->Execute();
    } // if
}

void ratchet::state::ai::AIState::Enter(void) {
    _behaviour_executor->Reset();
}

void ratchet::state::ai::AIState::Exit(void) {
}
#ifdef _DEBUG
void ratchet::state::ai::AIState::DebugRender(void) {
    _behaviour_executor->DebugRender();
}
#endif // _DEBUG