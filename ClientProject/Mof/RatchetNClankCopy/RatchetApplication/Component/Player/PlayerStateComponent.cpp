#include "PlayerStateComponent.h"


ratchet::PlayerStateComponent::PlayerStateComponent(int priority) :
    super(priority) {
}

ratchet::PlayerStateComponent::PlayerStateComponent(const PlayerStateComponent& obj) :
    super(obj) {
}

ratchet::PlayerStateComponent::~PlayerStateComponent() {
}

std::string ratchet::PlayerStateComponent::GetType(void) const {
    return "PlayerStateComponent";
}

bool ratchet::PlayerStateComponent::Initialize(void) {
    super::Initialize();
    this->ChangeState("PlayerActionIdleState");
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerStateComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerStateComponent>(*this);
}

bool ratchet::PlayerStateComponent::CanTransition(std::string_view next) const {
    using Type = state::PlayerActionStateType;

    auto current = _state_machine.GetCurrentStateName();
    if (next == Type::kPlayerActionJumpLandingState) {
        if (current == Type::kPlayerActionJumpDownState) {
            return true;
        } // if
        else if (current == Type::kPlayerActionDamageState) {
            return false;
        } // else if
        else if (current == Type::kPlayerActionJumpAttackState) {
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
    else if (next == Type::kPlayerActionThrowAttackSetState) {
        if (current == Type::kPlayerActionCrouchState) {
            return true;
        } // if
    } // else if
    return false;
}
#ifdef _DEBUG
bool ratchet::PlayerStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 100.0f, "player state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG