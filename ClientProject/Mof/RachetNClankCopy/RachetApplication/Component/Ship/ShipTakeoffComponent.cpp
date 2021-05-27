#include "ShipTakeoffComponent.h"


my::ShipTakeoffComponent::ShipTakeoffComponent(int priority) :
    super(priority) {
}

my::ShipTakeoffComponent::ShipTakeoffComponent(const ShipTakeoffComponent& obj) :
    super(obj) {
}

my::ShipTakeoffComponent::~ShipTakeoffComponent() {
}

std::string my::ShipTakeoffComponent::GetType(void) const {
    return "ShipTakeoffComponent";
}

std::string_view my::ShipTakeoffComponent::GetStateType(void) const {
    return state::ShipActionStateType::kShipActionTakeoffState;
}

bool my::ShipTakeoffComponent::Update(float delta_time) {
    auto pos = super::GetOwner()->GetPosition();
    pos.y += 0.1f;
    super::GetOwner()->SetPosition(pos);
    return true;
}

std::shared_ptr<my::Component> my::ShipTakeoffComponent::Clone(void) {
    return std::make_shared<my::ShipTakeoffComponent>(*this);
}

bool my::ShipTakeoffComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::ShipMotionStateType::kShipMotionTakeoffState);

    /*
    if (auto motion_com = _motion_com.lock()) {
        motion_com->ChangeMotion(my::Ship::MotionType::Default);
        _timer.Initialize(7.0f, false);
    } // if
    */

    return true;
}