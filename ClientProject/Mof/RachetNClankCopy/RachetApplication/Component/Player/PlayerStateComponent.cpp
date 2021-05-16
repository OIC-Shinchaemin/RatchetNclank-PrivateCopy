#include "PlayerStateComponent.h"

#include "../../State/PlayerActionStateDefine.h"


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
    
    std::vector<std::weak_ptr<my::ActionComponent>> work;
    super::GetOwner()->GetComponents<my::ActionComponent>(work);
    for (auto weak : work) {
        if (auto com = weak.lock()) {
            this->RegisterState(_state_machine, com);
        } // if
    } // for
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