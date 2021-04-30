#include "PlayerStateComponent.h"

#include "../../State/PlayerAction/PlayerActionIdleState.h"
#include "../../State/PlayerAction/PlayerActionMoveState.h"
#include "../../State/PlayerAction/PlayerActionJumpSetState.h"
#include "../../State/PlayerAction/PlayerActionJumpUpState.h"
#include "../../State/PlayerAction/PlayerActionJumpDownState.h"
#include "../../State/PlayerAction/PlayerActionJumpLandingState.h"


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

bool my::PlayerStateComponent::CanTransition(const std::string& name) {
    if (name == state::PlayerActionStateType::kPlayerActionJumpLandingState) {
        if (_state_machine.GetCurrentStateName() == state::PlayerActionStateType::kPlayerActionJumpDownState) {
            return true;
        } // if
    } // if
    return false;
}