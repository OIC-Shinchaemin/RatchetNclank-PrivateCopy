#include "ShipIdleComponent.h"


ratchet::component::ship::ShipIdleComponent::ShipIdleComponent(int priority) :
    super(priority) {
}

ratchet::component::ship::ShipIdleComponent::ShipIdleComponent(const ShipIdleComponent& obj) :
    super(obj) {
}

ratchet::component::ship::ShipIdleComponent::~ShipIdleComponent() {
}

std::string ratchet::component::ship::ShipIdleComponent::GetType(void) const {
    return "ShipIdleComponent";
}

std::string_view ratchet::component::ship::ShipIdleComponent::GetStateType(void) const {
    return state::ShipActionStateType::kShipActionIdleState;
}

bool ratchet::component::ship::ShipIdleComponent::Initialize(void) {
    super::Initialize();

    return true;
}

bool ratchet::component::ship::ShipIdleComponent::Update(float delta_time) {
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::ship::ShipIdleComponent::Clone(void) {
    return std::make_shared<ratchet::component::ship::ShipIdleComponent>(*this);
}

bool ratchet::component::ship::ShipIdleComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::ShipMotionStateType::kShipMotionIdleState);
    return true;
}