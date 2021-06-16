#include "ShipStateComponent.h"


ratchet::component::ship::ShipStateComponent::ShipStateComponent(int priority) :
    super(priority) {
}

ratchet::component::ship::ShipStateComponent::ShipStateComponent(const ShipStateComponent& obj) :
    super(obj) {
}

ratchet::component::ship::ShipStateComponent::~ShipStateComponent() {
}

std::string ratchet::component::ship::ShipStateComponent::GetType(void) const {
    return "ShipStateComponent";
}

bool ratchet::component::ship::ShipStateComponent::Initialize(void) {
    super::Initialize();
    super::ChangeState(state::ShipActionStateType::kShipActionLandingState);
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::ship::ShipStateComponent::Clone(void) {
    return std::make_shared<ratchet::component::ship::ShipStateComponent>(*this);
}

bool ratchet::component::ship::ShipStateComponent::CanTransition(std::string_view next) const {
    using Type = state::ShipActionStateType;
    auto current = _state_machine.GetCurrentStateName();
    if (current == Type::kShipActionIdleState) {
        if (next == Type::kShipActionTakeoffState) {
            return true;
        } // if
    } // if
    else if (current == Type::kShipActionLandingState) {
        if (next == Type::kShipActionIdleState) {
            return true;
        } // if
    } // else if
    else if (current == Type::kShipActionTakeoffState) {
        if (next == Type::kShipActionLandingState) {
            return true;
        } // if
    } // else if
    return false;
}

#ifdef _DEBUG
bool ratchet::component::ship::ShipStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 100.0f, "ship state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG