#include "RegisterGlobalCameraEvent.h"


rachet::RegisterGlobalCameraEvent::RegisterGlobalCameraEvent() :
    super() {
}

rachet::RegisterGlobalCameraEvent::~RegisterGlobalCameraEvent() {
}

void rachet::RegisterGlobalCameraEvent::OnNotify(const rachet::CameraController::CameraInfo& info) {
}

bool rachet::RegisterGlobalCameraEvent::Initialize(void) {
    return true;
}

bool rachet::RegisterGlobalCameraEvent::Update(float delta_time) {
    return true;
}