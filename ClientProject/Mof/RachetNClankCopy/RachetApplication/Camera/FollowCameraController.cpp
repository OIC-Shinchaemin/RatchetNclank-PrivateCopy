#include "FollowCameraController.h"


void my::FollowCameraController::UpdateCameraPosition(float delta_time, const std::shared_ptr<my::Camera>& camera) {
    camera->SetTarget(_target);

    auto& [azimuth, altitude, distance, spring, dumping, velocity] = _param;

    auto offset = math::SphericalToCartesian(distance, azimuth(), altitude());
    auto ideal_pos = _target + offset;

    auto displace = _position - ideal_pos;
    auto accel = (displace * (-spring)) - (velocity * dumping);

    velocity += accel * delta_time;
    _position += velocity * delta_time;

    camera->SetPosition(_position);
}

my::FollowCameraController::FollowCameraController() :
    super() {
    _param.distance = 8.0f;
    _param.azimuth = 270.0f;
    _param.altitude = this->GetDefaultAltitude();
    _param.spring = 30.0f;
    _param.dumping = std::sqrtf(_param.spring) * 2.0f;
}

my::FollowCameraController::~FollowCameraController() {
}

bool my::FollowCameraController::Update(float delta_time, const my::CameraController::CameraInfo& info) {
    _preview_position = _position;
    _target = info.target;
    this->UpdateCameraPosition(delta_time, _camera);
    return true;
}