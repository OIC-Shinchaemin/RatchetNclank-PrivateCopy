#include "ShipTakeoffComponent.h"


ratchet::component::ship::ShipTakeoffComponent::ShipTakeoffComponent(int priority) :
    super(priority),
    _timer(),
    _takeoff(false) {
}

ratchet::component::ship::ShipTakeoffComponent::ShipTakeoffComponent(const ShipTakeoffComponent& obj) :
    super(obj),
    _timer(),
    _takeoff(false) {
}

ratchet::component::ship::ShipTakeoffComponent::~ShipTakeoffComponent() {
}

std::string ratchet::component::ship::ShipTakeoffComponent::GetType(void) const {
    return "ShipTakeoffComponent";
}

std::string_view ratchet::component::ship::ShipTakeoffComponent::GetStateType(void) const {
    return state::ShipActionStateType::kShipActionTakeoffState;
}

bool ratchet::component::ship::ShipTakeoffComponent::Update(float delta_time) {
    if (_timer.Tick(delta_time)) {
        _takeoff = true;
    } // if
    if (_takeoff) {
        auto pos = super::GetOwner()->GetPosition();
        pos.y += 0.1f;
        super::GetOwner()->SetPosition(pos);
    } // if
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::ship::ShipTakeoffComponent::Clone(void) {
    return std::make_shared<ratchet::component::ship::ShipTakeoffComponent>(*this);
}

bool ratchet::component::ship::ShipTakeoffComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::ShipMotionStateType::kShipMotionTakeoffState);
    _timer.Initialize(7.0f, false);


    return true;
}