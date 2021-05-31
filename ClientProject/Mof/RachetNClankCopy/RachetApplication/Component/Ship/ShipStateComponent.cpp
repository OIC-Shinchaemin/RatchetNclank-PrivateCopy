#include "ShipStateComponent.h"


my::ShipStateComponent::ShipStateComponent(int priority) :
    super(priority) {
}

my::ShipStateComponent::ShipStateComponent(const ShipStateComponent& obj) :
    super(obj) {
}

my::ShipStateComponent::~ShipStateComponent() {
}

std::string my::ShipStateComponent::GetType(void) const {
    return "ShipStateComponent";
}

bool my::ShipStateComponent::Initialize(void) {
    super::Initialize();
    super::ChangeState(state::ShipActionStateType::kShipActionLandingState);
    return true;
}

std::shared_ptr<my::Component> my::ShipStateComponent::Clone(void) {
    return std::make_shared<my::ShipStateComponent>(*this);
}

bool my::ShipStateComponent::CanTransition(std::string_view next) const {
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
bool my::ShipStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 100.0f, "ship state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG