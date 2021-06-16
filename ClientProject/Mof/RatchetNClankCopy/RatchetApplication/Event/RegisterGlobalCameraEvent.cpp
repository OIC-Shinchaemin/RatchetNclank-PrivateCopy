#include "RegisterGlobalCameraEvent.h"


ratchet::event::RegisterGlobalCameraEvent::RegisterGlobalCameraEvent() :
    super() {
}

ratchet::event::RegisterGlobalCameraEvent::~RegisterGlobalCameraEvent() {
}

void ratchet::event::RegisterGlobalCameraEvent::OnNotify(const ratchet::camera::CameraController::CameraInfo& info) {
}

bool ratchet::event::RegisterGlobalCameraEvent::Initialize(void) {
    return true;
}

bool ratchet::event::RegisterGlobalCameraEvent::Update(float delta_time) {
    return true;
}