#include "CameraLocator.h"

#include "CameraManager.h"
#include "Camera.h"


std::weak_ptr<my::CameraManager> my::ServiceLocator<my::CameraManager>::_service;


my::CameraLocator::CameraLocator() {
}

my::CameraLocator::~CameraLocator() {
}

void my::CameraLocator::RegisterGlobalCamera(const std::shared_ptr<my::Camera>& ptr) {
    _ASSERT_EXPR(super::GetService(), L"無効なポインタを参照しています");
    super::GetService()->RegisterGlobalCamera(ptr);
}