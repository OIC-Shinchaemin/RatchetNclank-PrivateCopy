#include "AIPatrolState.h"


state::AIPatrolState::AIPatrolState() :
    super() {
    //super::_behaviour_path = "../Resource/behaviour/patrol.json";
    super::_behaviour_path = "../Resource/behaviour/test.json";
    this->GenerateBehaviourExecutor();
}

state::AIPatrolState::~AIPatrolState() {
}

const char* state::AIPatrolState::GetName(void) const {
    return "AIPatrolState";
}