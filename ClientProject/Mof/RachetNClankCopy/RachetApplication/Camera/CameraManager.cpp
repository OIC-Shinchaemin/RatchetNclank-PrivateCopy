#include "CameraManager.h"

my::CameraManager::CameraManager() :
	_global_camera() {
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