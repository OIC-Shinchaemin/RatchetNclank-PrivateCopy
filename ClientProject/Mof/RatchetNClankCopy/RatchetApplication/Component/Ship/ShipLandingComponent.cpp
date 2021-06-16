#include "ShipLandingComponent.h"


ratchet::component::ship::ShipLandingComponent::ShipLandingComponent(int priority) :
    super(priority) {
}

ratchet::component::ship::ShipLandingComponent::ShipLandingComponent(const ShipLandingComponent& obj) :
    super(obj) {
}

ratchet::component::ship::ShipLandingComponent::~ShipLandingComponent() {
}

std::string ratchet::component::ship::ShipLandingComponent::GetType(void) const {
    return "ShipLandingComponent";
}

std::string_view ratchet::component::ship::ShipLandingComponent::GetStateType(void) const {
    return state::ShipActionStateType::kShipActionLandingState;
}

void ratchet::component::ship::ShipLandingComponent::AddObserver(const std::shared_ptr<base::core::Observer<const ratchet::camera::CameraController::CameraInfo&>>& ptr) {
    Observable::AddObserver(ptr);
}

bool ratchet::component::ship::ShipLandingComponent::Update(float delta_time) {
    auto pos = super::GetOwner()->GetPosition();
    pos.y -= 0.1f;
    super::GetOwner()->SetPosition(pos);
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::ship::ShipLandingComponent::Clone(void) {
    return std::make_shared<ratchet::component::ship::ShipLandingComponent>(*this);
}

bool ratchet::component::ship::ShipLandingComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::ShipMotionStateType::kShipMotionLandingState);
    return true;
}

bool ratchet::component::ship::ShipLandingComponent::End(void) {
    super::End();

    auto camera_info = ratchet::camera::CameraController::CameraInfo();
    auto global = ::CGraphicsUtilities::GetCamera();

    camera_info.start_position = global->GetViewPosition();
    camera_info.camera_front = global->GetViewFront();
    Observable::Notify(camera_info);
    return true;
}