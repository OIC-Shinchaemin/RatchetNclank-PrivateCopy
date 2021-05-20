#include "FirstPersonCameraController.h"


void my::FirstPersonCameraController::UpdateCameraPosition(float delta_time, const my::CameraController::CameraInfo& info, const std::shared_ptr<my::Camera>& camera) {
    /*
    camera->SetTarget(_target);

    auto& [azimuth, altitude, distance, spring, dumping, velocity] = _param;

    auto offset = math::SphericalToCartesian(distance, azimuth(), altitude());
    auto ideal_pos = _target + offset;

    auto displace = _position - ideal_pos;
    auto accel = (displace * (-spring)) - (velocity * dumping);

    velocity += accel * delta_time;
    _position += velocity * delta_time;
    */

    auto pos = info.position;
    pos.y += 1.0f;
         
    camera->SetPosition(pos);
    pos.z += 1.0f;

    camera->SetTarget(pos);
}

my::FirstPersonCameraController::FirstPersonCameraController() :
    super() {
}

my::FirstPersonCameraController::~FirstPersonCameraController() {
}

bool my::FirstPersonCameraController::Update(float delta_time, const my::CameraController::CameraInfo& info) {
    _preview_position = _position;
    this->UpdateCameraPosition(delta_time, info, _camera);
    return true;
}