#include "Camera.h"

#include "Base/Core/Define.h"
#include "Base/Core/Math.h"


ratchet::camera::Camera::Camera() :
    _camera(),
    _position(),
    _target(),
    _up(math::vec3::kUnitY) {
}

ratchet::camera::Camera::~Camera() {
}

void ratchet::camera::Camera::SetPosition(Mof::CVector3 position) {
    this->_position = position;
}

void ratchet::camera::Camera::SetTarget(Mof::CVector3 target) {
    this->_target = target;
}

Mof::CVector3 ratchet::camera::Camera::GetPosition(void) {
    return _camera.GetViewPosition();
}

Mof::CVector3 ratchet::camera::Camera::GetTarget(void) const {
    return this->_target;
}

Mof::CVector3 ratchet::camera::Camera::GetViewFront(void) {
    return _camera.GetViewFront();
}

bool ratchet::camera::Camera::Initialize(void) {
    // ƒJƒƒ‰‰Šú‰»
    _camera.SetViewPort();
    //_camera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 2000.0f);
    float width = ::g_pFramework->GetWindow()->GetWidth();
    float height= ::g_pFramework->GetWindow()->GetHeight();
    _camera.PerspectiveFov(MOF_ToRadian(60.0f), width / height, 0.01f, 2000.0f);
    this->Update();
    return true;
}

bool ratchet::camera::Camera::Update(void) {
    _camera.LookAt(_position, _target, _up);
    return _camera.Update();
}

void ratchet::camera::Camera::RegisterGlobalCamera(void) {
    ::CGraphicsUtilities::SetCamera(&_camera);
}