#include "PlayerStateComponent.h"

#include "../../State/PlayerAction/PlayerActionIdleState.h"
#include "../../State/PlayerAction/PlayerActionMoveState.h"
#include "../../State/PlayerAction/PlayerActionJumpSetState.h"
#include "../../State/PlayerAction/PlayerActionJumpUpState.h"
#include "../../State/PlayerAction/PlayerActionJumpDownState.h"
#include "../../State/PlayerAction/PlayerActionJumpLandingState.h"
#include "../../State/PlayerAction/PlayerActionDoubleJumpState.h"
#include "../../State/PlayerAction/PlayerActionMeleeAttackOneState.h"
#include "../../State/PlayerAction/PlayerActionMeleeAttackOneEndState.h"
#include "../../State/PlayerAction/PlayerActionMeleeAttackTwoState.h"
#include "../../State/PlayerAction/PlayerActionMeleeAttackTwoEndState.h"
#include "../../State/PlayerAction/PlayerActionMeleeAttackThreeState.h"
#include "../../State/PlayerAction/PlayerActionMeleeAttackThreeEndState.h"
#include "../../State/PlayerAction/PlayerActionDamageState.h"
#include "../../State/PlayerAction/PlayerActionDeadState.h"


my::PlayerStateComponent::PlayerStateComponent(int priority) :
    super(priority),
    _state_machine() {
}

my::PlayerStateComponent::PlayerStateComponent(const PlayerStateComponent& obj) :
    super(obj._priority),
    _state_machine(obj._state_machine) {
}

my::PlayerStateComponent::~PlayerStateComponent() {
}

void my::PlayerStateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string my::PlayerStateComponent::GetType(void) const {
    return "PlayerStateComponent";
}

bool my::PlayerStateComponent::Initialize(void) {
    super::Initialize();
    super::Start();

    // state
    this->RegisterState<state::PlayerActionIdleState>(_state_machine);
    this->RegisterState<state::PlayerActionMoveState>(_state_machine);
    this->RegisterState<state::PlayerActionJumpSetState>(_state_machine);
    this->RegisterState<state::PlayerActionJumpUpState>(_state_machine);
    this->RegisterState<state::PlayerActionJumpDownState>(_state_machine);
    this->RegisterState<state::PlayerActionJumpLandingState>(_state_machine);
    this->RegisterState<state::PlayerActionDoubleJumpState>(_state_machine);
    this->RegisterState<state::PlayerActionMeleeAttackOneState>(_state_machine);
    this->RegisterState<state::PlayerActionMeleeAttackOneEndState>(_state_machine);
    this->RegisterState<state::PlayerActionMeleeAttackTwoState>(_state_machine);
    this->RegisterState<state::PlayerActionMeleeAttackTwoEndState>(_state_machine);
    this->RegisterState<state::PlayerActionMeleeAttackThreeState>(_state_machine);
    this->RegisterState<state::PlayerActionMeleeAttackThreeEndState>(_state_machine);
    this->RegisterState<state::PlayerActionDamageState>(_state_machine);
    this->RegisterState<state::PlayerActionDeadState>(_state_machine);
    _state_machine.ChangeState("PlayerActionIdleState");
    return true;
}

bool my::PlayerStateComponent::Update(float delta_time) {
    _state_machine.Update(delta_time);
    return false;
}

bool my::PlayerStateComponent::Release(void) {
    super::Release();
    _state_machine.Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerStateComponent::Clone(void) {
    return std::make_shared<my::PlayerStateComponent>(*this);
}

void my::PlayerStateComponent::ChangeState(const std::string& name) {
    _state_machine.ChangeState(name);
}

bool my::PlayerStateComponent::CanTransition(const std::string& next) {
    using Type = state::PlayerActionStateType;

    auto current = _state_machine.GetCurrentStateName();
    if (next == Type::kPlayerActionJumpLandingState) {
        if (current == Type::kPlayerActionJumpDownState) {
            return true;
        } // if
        else if (current == Type::kPlayerActionDamageState) {
            return false;
        } // else if
    } // if
    if (next == Type::kPlayerActionDamageState) {
        if (current == Type::kPlayerActionDamageState) {
            return false;
        } // if
        else if (current == Type::kPlayerActionDeadState) {
            return false;
        } // if
        else {
            return true;
        } // else
    } // if
    return false;
}