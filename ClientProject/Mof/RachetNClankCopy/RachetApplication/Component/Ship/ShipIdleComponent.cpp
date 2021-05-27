#include "ShipIdleComponent.h"


my::ShipIdleComponent::ShipIdleComponent(int priority) :
    super(priority) {
}

my::ShipIdleComponent::ShipIdleComponent(const ShipIdleComponent& obj) :
    super(obj) {
}

my::ShipIdleComponent::~ShipIdleComponent() {
}

std::string my::ShipIdleComponent::GetType(void) const {
    return "ShipIdleComponent";
}

std::string_view my::ShipIdleComponent::GetStateType(void) const {
    return state::ShipActionStateType::kShipActionIdleState;
}

bool my::ShipIdleComponent::Initialize(void) {
    super::Initialize();

    return true;
}

bool my::ShipIdleComponent::Update(float delta_time) {
    return true;
}

std::shared_ptr<my::Component> my::ShipIdleComponent::Clone(void) {
    return std::make_shared<my::ShipIdleComponent>(*this);
}

bool my::ShipIdleComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::ShipMotionStateType::kShipMotionIdleState);
    return true;
}