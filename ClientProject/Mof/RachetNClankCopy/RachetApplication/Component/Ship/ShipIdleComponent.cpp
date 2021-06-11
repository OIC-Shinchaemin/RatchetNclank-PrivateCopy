#include "ShipIdleComponent.h"


rachet::ShipIdleComponent::ShipIdleComponent(int priority) :
    super(priority) {
}

rachet::ShipIdleComponent::ShipIdleComponent(const ShipIdleComponent& obj) :
    super(obj) {
}

rachet::ShipIdleComponent::~ShipIdleComponent() {
}

std::string rachet::ShipIdleComponent::GetType(void) const {
    return "ShipIdleComponent";
}

std::string_view rachet::ShipIdleComponent::GetStateType(void) const {
    return state::ShipActionStateType::kShipActionIdleState;
}

bool rachet::ShipIdleComponent::Initialize(void) {
    super::Initialize();

    return true;
}

bool rachet::ShipIdleComponent::Update(float delta_time) {
    return true;
}

std::shared_ptr<rachet::Component> rachet::ShipIdleComponent::Clone(void) {
    return std::make_shared<rachet::ShipIdleComponent>(*this);
}

bool rachet::ShipIdleComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::ShipMotionStateType::kShipMotionIdleState);
    return true;
}