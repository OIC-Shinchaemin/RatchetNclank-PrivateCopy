#include "ShipLandingComponent.h"


my::ShipLandingComponent::ShipLandingComponent(int priority) :
    super(priority) {
}

my::ShipLandingComponent::ShipLandingComponent(const ShipLandingComponent& obj) :
    super(obj) {
}

my::ShipLandingComponent::~ShipLandingComponent() {
}

std::string my::ShipLandingComponent::GetType(void) const {
    return "ShipLandingComponent";
}

std::string_view my::ShipLandingComponent::GetStateType(void) const {
    return state::ShipActionStateType::kShipActionLandingState;
}

bool my::ShipLandingComponent::Update(float delta_time) {
    return true;
}

std::shared_ptr<my::Component> my::ShipLandingComponent::Clone(void) {
    return std::make_shared<my::ShipLandingComponent>(*this);
}

bool my::ShipLandingComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::ShipMotionStateType::kShipMotionLandingState);
    return true;
}