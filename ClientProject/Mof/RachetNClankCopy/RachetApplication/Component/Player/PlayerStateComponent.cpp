#include "PlayerStateComponent.h"

#include "../../State/PlayerActionStateDefine.h"
#include "../Player/PlayerIdleComponent.h"
#include "../Player/PlayerMoveComponent.h"
#include "../Player/PlayerJumpSetComponent.h"
#include "../Player/PlayerJumpUpComponent.h"
#include "../Player/PlayerJumpDownComponent.h"
#include "../Player/PlayerJumpLandingComponent.h"
#include "../Player/PlayerDoubleJumpComponent.h"
#include "../Player/PlayerMeleeAttackOneComponent.h"
#include "../Player/PlayerMeleeAttackOneEndComponent.h"
#include "../Player/PlayerMeleeAttackTwoComponent.h"
#include "../Player/PlayerMeleeAttackTwoEndComponent.h"
#include "../Player/PlayerMeleeAttackThreeComponent.h"
#include "../Player/PlayerMeleeAttackThreeEndComponent.h"
#include "../Player/PlayerDamageComponent.h"
#include "../Player/PlayerDeadComponent.h"



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

    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerIdleComponent>());
    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerMoveComponent>());
    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerJumpSetComponent>());
    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerJumpUpComponent>());
    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerJumpDownComponent>());
    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerJumpLandingComponent>());
    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerDoubleJumpComponent>());
    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerMeleeAttackOneComponent>());
    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerMeleeAttackOneEndComponent>());
    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerMeleeAttackTwoComponent>());
    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerMeleeAttackTwoEndComponent>());
    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerMeleeAttackThreeComponent>());
    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerMeleeAttackThreeEndComponent>());
    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerDamageComponent>());
    this->RegisterState(_state_machine, super::GetOwner()->GetComponent<my::PlayerDeadComponent>());

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