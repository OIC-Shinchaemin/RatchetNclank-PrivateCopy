#include "ShipIdleComponent.h"


ratchet::ShipIdleComponent::ShipIdleComponent(int priority) :
    super(priority) {
}

ratchet::ShipIdleComponent::ShipIdleComponent(const ShipIdleComponent& obj) :
    super(obj) {
}

ratchet::ShipIdleComponent::~ShipIdleComponent() {
}

std::string ratchet::ShipIdleComponent::GetType(void) const {
    return "ShipIdleComponent";
}

std::string_view ratchet::ShipIdleComponent::GetStateType(void) const {
    return state::ShipActionStateType::kShipActionIdleState;
}

bool ratchet::ShipIdleComponent::Initialize(void) {
    super::Initialize();

    return true;
}

bool ratchet::ShipIdleComponent::Update(float delta_time) {
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::ShipIdleComponent::Clone(void) {
    return std::make_shared<ratchet::ShipIdleComponent>(*this);
}

bool ratchet::ShipIdleComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::ShipMotionStateType::kShipMotionIdleState);
    return true;
}