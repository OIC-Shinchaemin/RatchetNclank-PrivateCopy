#include "Camera.h"

#include "Base/Core/Define.h"
#include "Base/Core/Math.h"


rachet::Camera::Camera() :
    _camera(),
    _position(),
    _target(),
    _up(math::vec3::kUnitY) {
}

rachet::Camera::~Camera() {
}

void rachet::Camera::SetPosition(Mof::CVector3 position) {
    this->_position = position;
}

void rachet::Camera::SetTarget(Mof::CVector3 target) {
    this->_target = target;
}

Mof::CVector3 rachet::Camera::GetPosition(void) {
    return _camera.GetViewPosition();
}

Mof::CVector3 rachet::Camera::GetTarget(void) const {
    return this->_target;
}

Mof::CVector3 rachet::Camera::GetViewFront(void) {
    return _camera.GetViewFront();
}

bool rachet::Camera::Initialize(void) {
    // ƒJƒƒ‰‰Šú‰»
    _camera.SetViewPort();
    _camera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 2000.0f);
    this->Update();
    return true;
}

bool rachet::Camera::Update(void) {
    _camera.LookAt(_position, _target, _up);
    return _camera.Update();
}

void rachet::Camera::RegisterGlobalCamera(void) {
    ::CGraphicsUtilities::SetCamera(&_camera);
}