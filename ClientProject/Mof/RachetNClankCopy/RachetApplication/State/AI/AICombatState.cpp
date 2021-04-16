#include "AICombatState.h"


state::AICombatState::AICombatState() :
    super() {
    super::_behaviour_path = "../Resource/behaviour/combat.json";
}

state::AICombatState ::~AICombatState() {
}

const char* state::AICombatState::GetName(void) const {
    return "AICombatState";
}