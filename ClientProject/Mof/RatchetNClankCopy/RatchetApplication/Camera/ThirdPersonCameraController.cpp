#include "ThirdPersonCameraController.h"


void ratchet::camera::ThirdPersonCameraController::UpdateCameraPosition(float delta_time, const std::shared_ptr<ratchet::camera::Camera>& camera) {
    camera->SetTarget(_target);
    camera->SetPosition(_position);
}

ratchet::camera::ThirdPersonCameraController::ThirdPersonCameraController() {
}

ratchet::camera::ThirdPersonCameraController::~ThirdPersonCameraController() {
}

bool ratchet::camera::ThirdPersonCameraController::Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info) {
    super::_previous_position= _position;
    _position = info.ideal_position;
    _target = info.target_position;
    this->UpdateCameraPosition(delta_time, _camera);
    return true;
}