#include "CameraManager.h"

#include "Base/Core/Math.h"


ratchet::CameraManager::CameraManager() :
    _global_camera(std::make_shared<ratchet::Camera>()) {
    _global_camera->SetPosition(math::vec3::kOne * 5.0f);
    _global_camera->SetTarget(math::vec3::kZero);
    _global_camera->Initialize();
    _global_camera->RegisterGlobalCamera();
}

ratchet::CameraManager::~CameraManager() {
}

void ratchet::CameraManager::RegisterGlobalCamera(const std::shared_ptr<ratchet::Camera>& ptr) {
    this->_global_camera = ptr;
    _global_camera->RegisterGlobalCamera();
}

bool ratchet::CameraManager::Update(void) {
    _global_camera->Update();
    return true;
}