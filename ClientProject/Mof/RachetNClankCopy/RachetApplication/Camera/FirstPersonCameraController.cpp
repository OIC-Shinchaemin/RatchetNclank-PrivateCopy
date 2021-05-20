#include "FirstPersonCameraController.h"


void my::FirstPersonCameraController::UpdateCameraPosition(float delta_time, const my::CameraController::CameraInfo& info, const std::shared_ptr<my::Camera>& camera) {
    camera->SetPosition(info.position);
    auto offset = math::vec3::kNegUnitZ;
    offset.RotateAround(math::vec3::kZero, info.rotate);
    camera->SetTarget(info.position + offset);
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