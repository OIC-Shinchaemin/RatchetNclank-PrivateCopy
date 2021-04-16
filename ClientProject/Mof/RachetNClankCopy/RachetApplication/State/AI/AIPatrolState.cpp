#include "AIPatrolState.h"


state::AIPatrolState::AIPatrolState() :
    super() {
    super::_behaviour_path = "../Resource/behaviour/patrol.json";
}

state::AIPatrolState::~AIPatrolState() {
}

const char* state::AIPatrolState::GetName(void) const {
    return "AIPatrolState";
}