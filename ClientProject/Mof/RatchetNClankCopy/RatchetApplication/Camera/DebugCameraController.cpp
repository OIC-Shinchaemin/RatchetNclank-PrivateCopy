#include "DebugCameraController.h"


ratchet::camera::DebugCameraController::DebugCameraController() :
    super() {
}

ratchet::camera::DebugCameraController::~DebugCameraController() {
}

bool ratchet::camera::DebugCameraController::Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info) {
    //this->SetCameraPosition(math::vec3::kOne * 10.0f);
    //this->SetCameraTarget(math::vec3::kZero);
    return true;
}