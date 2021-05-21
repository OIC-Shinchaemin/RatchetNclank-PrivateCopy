#include "FirstPersonCameraController.h"


void my::FirstPersonCameraController::UpdateCameraPosition(float delta_time, const my::CameraController::CameraInfo& info, const std::shared_ptr<my::Camera>& camera) {
}

my::FirstPersonCameraController::FirstPersonCameraController() :
    super() {
    _param.spring = 20.0f;
    _param.dumping = std::sqrtf(_param.spring) * 1.5f;
}

my::FirstPersonCameraController::~FirstPersonCameraController() {
}

void my::FirstPersonCameraController::SetInfo(const my::CameraController::CameraInfo& info) {
    _position = info.start_position;

    auto offset = math::vec3::kNegUnitZ;
    //auto angle_y = std::atan2(info.camera_front.z, info.camera_front.x) + math::kHalfPi;
    auto angle_y = std::atan2(info.camera_front.z, info.camera_front.x) ;
    auto angle = Mof::CVector3(0.0f, angle_y, 0.0f) ;

    offset.RotateAround(math::vec3::kZero, angle);
    _target = info.ideal_position + offset;
}

bool my::FirstPersonCameraController::Update(float delta_time, const my::CameraController::CameraInfo& info) {
    _preview_position = _position;

    auto displace = _position - info.ideal_position;
    auto accel = (displace * (-_param.spring)) - (_param.velocity * _param.dumping);

    _param.velocity += accel * delta_time;
    _position += _param.velocity * delta_time;
    _camera->SetPosition(_position);
    _camera->SetTarget(_target);
    return true;
}