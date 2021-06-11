#include "CameraManager.h"

#include "Base/Core/Math.h"


rachet::CameraManager::CameraManager() :
    _global_camera(std::make_shared<rachet::Camera>()) {
    _global_camera->SetPosition(math::vec3::kOne * 5.0f);
    _global_camera->SetTarget(math::vec3::kZero);
    _global_camera->Initialize();
    _global_camera->RegisterGlobalCamera();
}

rachet::CameraManager::~CameraManager() {
}

void rachet::CameraManager::RegisterGlobalCamera(const std::shared_ptr<rachet::Camera>& ptr) {
    this->_global_camera = ptr;
    _global_camera->RegisterGlobalCamera();
}

bool rachet::CameraManager::Update(void) {
    _global_camera->Update();
    return true;
}