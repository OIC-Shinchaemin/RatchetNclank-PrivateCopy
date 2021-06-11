#include "DebugCameraController.h"


rachet::DebugCameraController::DebugCameraController() :
    super() {
}

rachet::DebugCameraController::~DebugCameraController() {
}

bool rachet::DebugCameraController::Update(float delta_time, const rachet::CameraController::CameraInfo& info) {
    //this->SetCameraPosition(math::vec3::kOne * 10.0f);
    //this->SetCameraTarget(math::vec3::kZero);
    return true;
}