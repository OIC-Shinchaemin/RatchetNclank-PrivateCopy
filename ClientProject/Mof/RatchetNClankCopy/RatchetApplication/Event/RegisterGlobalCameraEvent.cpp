#include "RegisterGlobalCameraEvent.h"


ratchet::RegisterGlobalCameraEvent::RegisterGlobalCameraEvent() :
    super() {
}

ratchet::RegisterGlobalCameraEvent::~RegisterGlobalCameraEvent() {
}

void ratchet::RegisterGlobalCameraEvent::OnNotify(const ratchet::CameraController::CameraInfo& info) {
}

bool ratchet::RegisterGlobalCameraEvent::Initialize(void) {
    return true;
}

bool ratchet::RegisterGlobalCameraEvent::Update(float delta_time) {
    return true;
}