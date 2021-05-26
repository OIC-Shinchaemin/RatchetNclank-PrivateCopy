#include "FirstPersonCameraController.h"


my::FirstPersonCameraController::FirstPersonCameraController() :
    super() {
    _param.azimuth = 0.0f;
    _param.altitude = 0.0f;
    _param.distance = 1.0f;
    _param.spring = 25.0f;
    _param.dumping = std::sqrtf(_param.spring) * 1.5f;
}

my::FirstPersonCameraController::~FirstPersonCameraController() {
}

void my::FirstPersonCameraController::SetInfo(const my::CameraController::CameraInfo& info) {
    puts("FirstPersonCameraController");
    _position = info.start_position;

    auto offset = Mof::CVector3(math::vec3::kNegUnitZ * _param.distance);
    float angle_y = std::atan2(-info.camera_front.z, info.camera_front.x) - math::kHalfPi;
    auto angle = Mof::CVector3(0.0f, angle_y, 0.0f);

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

    auto target = _target;
    target.RotationY(_param.azimuth());
    _camera->SetTarget(target);
    return true;
}