#include "Camera.h"

#include "My/Core/Define.h"
#include "My/Core/Math.h"


my::Camera::Camera() :
    _camera(),
    _position(),
    _target(),
    _up(math::vec3::kUnitY) {
}

my::Camera::~Camera() {
}

void my::Camera::SetPosition(Mof::CVector3 position) {
    this->_position = position;
}

void my::Camera::SetTarget(Mof::CVector3 target) {
    this->_target = target;
}

Mof::CVector3 my::Camera::GetPosition(void) {
    return _camera.GetViewPosition();
}

Mof::CVector3 my::Camera::GetTarget(void) const {
    return this->_target;
}

Mof::CVector3 my::Camera::GetViewFront(void) {
    return _camera.GetViewFront();
}

bool my::Camera::Initialize(void) {
    // ƒJƒƒ‰‰Šú‰»
    _camera.SetViewPort();
    _camera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 1000.0f);
    this->Update();
    return true;
}

bool my::Camera::Update(void) {
    _camera.LookAt(_position, _target, _up);
    return _camera.Update();
}

void my::Camera::RegisterGlobalCamera(void) {
    ::CGraphicsUtilities::SetCamera(&_camera);
}