#include "AICombatState.h"


ratchet::state::ai::AICombatState::AICombatState() :
    super() {
}

ratchet::state::ai::AICombatState ::~AICombatState() {
}

const char* ratchet::state::ai::AICombatState::GetName(void) const {
    return "AICombatState";
}