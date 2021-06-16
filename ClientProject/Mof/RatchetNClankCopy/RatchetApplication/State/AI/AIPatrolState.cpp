#include "AIPatrolState.h"


ratchet::state::ai::AIPatrolState::AIPatrolState() :
    super() {
}

ratchet::state::ai::AIPatrolState::~AIPatrolState() {
}

const char* ratchet::state::ai::AIPatrolState::GetName(void) const {
    return "AIPatrolState";
}