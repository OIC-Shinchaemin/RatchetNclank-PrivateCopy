#include "ShipLandingComponent.h"


ratchet::ShipLandingComponent::ShipLandingComponent(int priority) :
    super(priority) {
}

ratchet::ShipLandingComponent::ShipLandingComponent(const ShipLandingComponent& obj) :
    super(obj) {
}

ratchet::ShipLandingComponent::~ShipLandingComponent() {
}

std::string ratchet::ShipLandingComponent::GetType(void) const {
    return "ShipLandingComponent";
}

std::string_view ratchet::ShipLandingComponent::GetStateType(void) const {
    return state::ShipActionStateType::kShipActionLandingState;
}

void ratchet::ShipLandingComponent::AddObserver(const std::shared_ptr<base::core::Observer<const ratchet::CameraController::CameraInfo&>>& ptr) {
    Observable::AddObserver(ptr);
}

bool ratchet::ShipLandingComponent::Update(float delta_time) {
    auto pos = super::GetOwner()->GetPosition();
    pos.y -= 0.1f;
    super::GetOwner()->SetPosition(pos);
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::ShipLandingComponent::Clone(void) {
    return std::make_shared<ratchet::ShipLandingComponent>(*this);
}

bool ratchet::ShipLandingComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::ShipMotionStateType::kShipMotionLandingState);
    return true;
}

bool ratchet::ShipLandingComponent::End(void) {
    super::End();

    auto camera_info = ratchet::CameraController::CameraInfo();
    auto global = ::CGraphicsUtilities::GetCamera();

    camera_info.start_position = global->GetViewPosition();
    camera_info.camera_front = global->GetViewFront();
    Observable::Notify(camera_info);
    return true;
}