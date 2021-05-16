#include "ShipComponent.h"

#include "../../Actor/Ship/Ship.h"
#include "../MotionComponent.h"
#include "../../Camera/FollowCameraController.h"


my::ShipComponent::ShipComponent(int priority) :
    super(priority) ,
    _timer(),
    _take_off(false),
    _camera_controller(),
    _motion_com(){
}

my::ShipComponent::ShipComponent(const ShipComponent& obj) :
    super(obj),
    _timer(),
    _take_off(false),
    _camera_controller(),
    _motion_com() {
}

my::ShipComponent::~ShipComponent() {
}

std::string my::ShipComponent::GetType(void) const {
    return "ShipComponent";
}

bool my::ShipComponent::Initialize(void) {
    super::Initialize();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    return true;
}

bool my::ShipComponent::Update(float delta_time) {
    if (_timer.Tick(delta_time)) {
        _take_off = true;
    } // if
    auto pos = super::GetOwner()->GetPosition();
    if (_take_off) {
        pos.y += 0.1f;
        super::GetOwner()->SetPosition(pos);
    } // if

    if (pos.y > 10.0f) {
        super::GetOwner()->Notify("GameClear", super::GetOwner());
    } // if
    return true;
}

bool my::ShipComponent::Activate(void) {
    if (super::IsActive()) {
        return false;
    } // if
    super::Activate();
    if (auto motion_com = _motion_com.lock()) {
        motion_com->ChangeMotion(my::Ship::MotionType::Default);
        _timer.Initialize(7.0f, false);
    } // if

    auto prev = ::CGraphicsUtilities::GetCamera();
    auto camera = std::make_shared<my::Camera>();
    camera->SetPosition(prev->GetViewPosition());
    camera->SetTarget(prev->GetTargetPosition());
    camera->Initialize();
    camera->Update();
    _camera_controller.SetService(std::make_shared<my::CameraController>());
    _camera_controller.GetService()->SetCamera(camera);
    _camera_controller.GetService()->RegisterGlobalCamera();
    return true;
}


std::shared_ptr<my::Component> my::ShipComponent::Clone(void) {
    return std::make_shared<my::ShipComponent>(*this);
}