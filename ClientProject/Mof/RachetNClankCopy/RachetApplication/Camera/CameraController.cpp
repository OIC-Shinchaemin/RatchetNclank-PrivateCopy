#include "CameraController.h"


std::weak_ptr<ratchet::CameraManager> ratchet::CameraController::_manager;


void ratchet::CameraController::SetCameraManager(const std::shared_ptr<ratchet::CameraManager>& ptr) {
    _manager = ptr;
}

ratchet::CameraController::CameraController() :
    _camera(),
    _position(),
    _target(),
    _preview_position() {
}

ratchet::CameraController::~CameraController() {
}

ratchet::CameraController::operator bool(void) const {
    return _camera.get();
}

void ratchet::CameraController::SetCamera(const std::shared_ptr<ratchet::Camera>& ptr) {
    this->_camera = ptr;
}

/*
void ratchet::CameraController::SetCameraPosition(Mof::CVector3 pos) {
    this->_position = pos;
}

void ratchet::CameraController::SetCameraTarget(Mof::CVector3 pos) {
    this->_target = pos;
}
*/

void ratchet::CameraController::SetDistance(float value) {
    this->_param.distance = value;
}

void ratchet::CameraController::SetAzimuth(float degree) {
    this->_param.azimuth = degree;
}

void ratchet::CameraController::SetAltitude(float degree) {
    this->_param.altitude = degree;
}

void ratchet::CameraController::SetSpring(float value) {
    this->_param.spring = value;
}

void ratchet::CameraController::SetDumping(float value) {
    this->_param.dumping = value;
}

void ratchet::CameraController::SetInfo(const ratchet::CameraController::CameraInfo& info) {
    _position = info.start_position;
    _target = info.target_position;
}

std::shared_ptr<ratchet::Camera> ratchet::CameraController::GetCamera(void) const {
    return this->_camera;
}

Mof::CVector3 ratchet::CameraController::GetCameraPosition(void) const {
    if (_camera) {
        return _camera->GetPosition();
    } // if
    return Mof::CVector3();
}

Mof::CVector3 ratchet::CameraController::GetViewFront(void) const {
    if (_camera) {
        return _camera->GetViewFront();
    } // if
    return Mof::CVector3();
}

float ratchet::CameraController::GetAzimuth(void) const {
    return this->_param.azimuth();
}

float ratchet::CameraController::GetAltitude(void) const {
    return this->_param.altitude();
}

float ratchet::CameraController::GetDefaultAzimuth(void) const {
    math::Radian value = 270.0f;
    return value();
}

float ratchet::CameraController::GetDefaultAltitude(void) const {
    math::Radian altitude = 25.0f;
    return altitude();
}

Mof::CVector3 ratchet::CameraController::GetVelocity(void) const {
    return this->_param.velocity;
}

Mof::CVector3 ratchet::CameraController::GetPreviewPosition(void) const {
    return this->_preview_position;
}

void ratchet::CameraController::AddAzimuth(float degree) {
    this->_param.azimuth += degree;
}

void ratchet::CameraController::AddAltitude(float degree) {
    _param.altitude += degree;
    if (_param.altitude <= -5.0f) {
        _param.altitude = -5.0f;
    } // if
    if (_param.altitude >= 45.0f) {
        _param.altitude = 45.0f;
    } // if
}

bool ratchet::CameraController::Update(float delta_time, const ratchet::CameraController::CameraInfo& info) {
    return true;
}

bool ratchet::CameraController::Release(void) {
    _camera.reset();
    return true;
}

bool ratchet::CameraController::RegisterGlobalCamera(void) {
    _ASSERT_EXPR(!_manager.expired(), L"–³Œø‚Èƒ|ƒCƒ“ƒ^‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚·");
    _manager.lock()->RegisterGlobalCamera(_camera);
    return true;
}