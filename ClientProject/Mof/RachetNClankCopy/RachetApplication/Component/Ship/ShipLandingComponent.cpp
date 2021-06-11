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

void my::ShipLandingComponent::AddObserver(const std::shared_ptr<base::core::Observer<const my::CameraController::CameraInfo&>>& ptr) {
    Observable::AddObserver(ptr);
}

bool my::ShipLandingComponent::Update(float delta_time) {
    auto pos = super::GetOwner()->GetPosition();
    pos.y -= 0.1f;
    super::GetOwner()->SetPosition(pos);
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

bool my::ShipLandingComponent::End(void) {
    super::End();

    auto camera_info = my::CameraController::CameraInfo();
    auto global = ::CGraphicsUtilities::GetCamera();

    camera_info.start_position = global->GetViewPosition();
    camera_info.camera_front = global->GetViewFront();
    Observable::Notify(camera_info);
    return true;
}