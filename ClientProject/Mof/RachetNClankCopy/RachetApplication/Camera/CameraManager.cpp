#include "CameraManager.h"

#include "Base/Core/Math.h"


my::CameraManager::CameraManager() :
    _global_camera(std::make_shared<my::Camera>()) {
    _global_camera->SetPosition(math::vec3::kOne * 5.0f);
    _global_camera->SetTarget(math::vec3::kZero);
    _global_camera->Initialize();
    _global_camera->RegisterGlobalCamera();
}

my::CameraManager::~CameraManager() {
}

void my::CameraManager::RegisterGlobalCamera(const std::shared_ptr<my::Camera>& ptr) {
    this->_global_camera = ptr;
    _global_camera->RegisterGlobalCamera();
}

bool my::CameraManager::Update(void) {
    _global_camera->Update();
    return true;
}