#include "AICombatState.h"


state::AICombatState::AICombatState() :
    super() {
}

state::AICombatState ::~AICombatState() {
}

const char* state::AICombatState::GetName(void) const {
    return "AICombatState";
}