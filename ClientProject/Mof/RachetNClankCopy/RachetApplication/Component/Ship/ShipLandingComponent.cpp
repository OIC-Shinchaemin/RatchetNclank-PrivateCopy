#include "ShipLandingComponent.h"


rachet::ShipLandingComponent::ShipLandingComponent(int priority) :
    super(priority) {
}

rachet::ShipLandingComponent::ShipLandingComponent(const ShipLandingComponent& obj) :
    super(obj) {
}

rachet::ShipLandingComponent::~ShipLandingComponent() {
}

std::string rachet::ShipLandingComponent::GetType(void) const {
    return "ShipLandingComponent";
}

std::string_view rachet::ShipLandingComponent::GetStateType(void) const {
    return state::ShipActionStateType::kShipActionLandingState;
}

void rachet::ShipLandingComponent::AddObserver(const std::shared_ptr<base::core::Observer<const rachet::CameraController::CameraInfo&>>& ptr) {
    Observable::AddObserver(ptr);
}

bool rachet::ShipLandingComponent::Update(float delta_time) {
    auto pos = super::GetOwner()->GetPosition();
    pos.y -= 0.1f;
    super::GetOwner()->SetPosition(pos);
    return true;
}

std::shared_ptr<rachet::Component> rachet::ShipLandingComponent::Clone(void) {
    return std::make_shared<rachet::ShipLandingComponent>(*this);
}

bool rachet::ShipLandingComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::ShipMotionStateType::kShipMotionLandingState);
    return true;
}

bool rachet::ShipLandingComponent::End(void) {
    super::End();

    auto camera_info = rachet::CameraController::CameraInfo();
    auto global = ::CGraphicsUtilities::GetCamera();

    camera_info.start_position = global->GetViewPosition();
    camera_info.camera_front = global->GetViewFront();
    Observable::Notify(camera_info);
    return true;
}