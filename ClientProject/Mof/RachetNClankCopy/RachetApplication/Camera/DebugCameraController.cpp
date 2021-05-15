#include "DebugCameraController.h"


my::DebugCameraController::DebugCameraController() :
    super() {
}

my::DebugCameraController::~DebugCameraController() {
}

bool my::DebugCameraController::Update(float delta_time) {
    this->SetCameraPosition(math::vec3::kOne * 10.0f);
    this->SetCameraTarget(math::vec3::kZero);
    return true;
}