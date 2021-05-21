#include "PlayerStateComponent.h"


my::PlayerStateComponent::PlayerStateComponent(int priority) :
    super(priority),
    _state_machine() {
}

my::PlayerStateComponent::PlayerStateComponent(const PlayerStateComponent& obj) :
    super(obj),
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

bool my::PlayerStateComponent::IsEqual(std::string_view state) const {
    return _state_machine.GetCurrentStateName() == state;
}

bool my::PlayerStateComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

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

bool my::PlayerStateComponent::CanTransition(std::string_view next) const {
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
    else if (next == Type::kPlayerActionDamageState) {
        if (current == Type::kPlayerActionDamageState) {
            return false;
        } // if
        else if (current == Type::kPlayerActionDeadState) {
            return false;
        } // if
        else {
            return true;
        } // else
    } // else if
    else if (next == Type::kPlayerActionIdleState) {
        if (current == Type::kPlayerActionJumpAttackState) {
            return true;
        } // if
    } // else if
    else if (next == Type::kPlayerActionJumpAttackState) {
        if (current == Type::kPlayerActionJumpAttackSetState) {
            return true;
        } // if
    } // else if
    return false;
}
#ifdef _DEBUG
bool my::PlayerStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 100.0f, "player state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG