#include "ShipTakeoffComponent.h"


rachet::ShipTakeoffComponent::ShipTakeoffComponent(int priority) :
    super(priority),
    _timer(),
    _takeoff(false) {
}

rachet::ShipTakeoffComponent::ShipTakeoffComponent(const ShipTakeoffComponent& obj) :
    super(obj),
    _timer(),
    _takeoff(false) {
}

rachet::ShipTakeoffComponent::~ShipTakeoffComponent() {
}

std::string rachet::ShipTakeoffComponent::GetType(void) const {
    return "ShipTakeoffComponent";
}

std::string_view rachet::ShipTakeoffComponent::GetStateType(void) const {
    return state::ShipActionStateType::kShipActionTakeoffState;
}

bool rachet::ShipTakeoffComponent::Update(float delta_time) {
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

std::shared_ptr<rachet::Component> rachet::ShipTakeoffComponent::Clone(void) {
    return std::make_shared<rachet::ShipTakeoffComponent>(*this);
}

bool rachet::ShipTakeoffComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::ShipMotionStateType::kShipMotionTakeoffState);
    _timer.Initialize(7.0f, false);


    return true;
}