#include "RegisterGlobalCameraEvent.h"


my::RegisterGlobalCameraEvent::RegisterGlobalCameraEvent() :
    super() {
}

my::RegisterGlobalCameraEvent::~RegisterGlobalCameraEvent() {
}

void my::RegisterGlobalCameraEvent::OnNotify(const my::CameraController::CameraInfo& info) {
}

bool my::RegisterGlobalCameraEvent::Initialize(void) {
    return true;
}

bool my::RegisterGlobalCameraEvent::Update(float delta_time) {
    return true;
}