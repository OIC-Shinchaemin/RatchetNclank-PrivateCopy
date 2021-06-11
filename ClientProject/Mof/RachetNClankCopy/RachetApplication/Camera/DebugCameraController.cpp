#include "DebugCameraController.h"


ratchet::DebugCameraController::DebugCameraController() :
    super() {
}

ratchet::DebugCameraController::~DebugCameraController() {
}

bool ratchet::DebugCameraController::Update(float delta_time, const ratchet::CameraController::CameraInfo& info) {
    //this->SetCameraPosition(math::vec3::kOne * 10.0f);
    //this->SetCameraTarget(math::vec3::kZero);
    return true;
}