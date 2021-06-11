#include "CameraManager.h"

#include "Base/Core/Math.h"


ratchet::camera::CameraManager::CameraManager() :
    _global_camera(std::make_shared<ratchet::camera::Camera>()) {
    _global_camera->SetPosition(math::vec3::kOne * 5.0f);
    _global_camera->SetTarget(math::vec3::kZero);
    _global_camera->Initialize();
    _global_camera->RegisterGlobalCamera();
}

ratchet::camera::CameraManager::~CameraManager() {
}

void ratchet::camera::CameraManager::RegisterGlobalCamera(const std::shared_ptr<ratchet::camera::Camera>& ptr) {
    this->_global_camera = ptr;
    _global_camera->RegisterGlobalCamera();
}

bool ratchet::camera::CameraManager::Update(void) {
    _global_camera->Update();
    return true;
}