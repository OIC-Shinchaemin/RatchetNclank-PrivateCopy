#include "CameraController.h"


std::weak_ptr<ratchet::camera::CameraManager> ratchet::camera::CameraController::_manager;


void ratchet::camera::CameraController::SetCameraManager(const std::shared_ptr<ratchet::camera::CameraManager>& ptr) {
    _manager = ptr;
}

ratchet::camera::CameraController::CameraController() :
    _camera(),
    _position(),
    _target(),
    _previous_position(),
    _update_position_flag(true){
}

ratchet::camera::CameraController::~CameraController() {
}

ratchet::camera::CameraController::operator bool(void) const {
    return _camera.get();
}

void ratchet::camera::CameraController::SetCamera(const std::shared_ptr<ratchet::camera::Camera>& ptr) {
    this->_camera = ptr;
}

void ratchet::camera::CameraController::SetDistance(float value) {
    this->_param.distance = value;
}

void ratchet::camera::CameraController::SetAzimuth(float degree) {
    this->_param.azimuth = degree;
}

void ratchet::camera::CameraController::SetAltitude(float degree) {
    this->_param.altitude = degree;
}

void ratchet::camera::CameraController::SetSpring(float value) {
    this->_param.spring = value;
}

void ratchet::camera::CameraController::SetDumping(float value) {
    this->_param.dumping = value;
}

void ratchet::camera::CameraController::SetUseSpring(bool flag) {
    this->_use_spring = flag;
}

void ratchet::camera::CameraController::SetUpdatePositionFlag(bool flag) {
    this->_update_position_flag = flag;
}

void ratchet::camera::CameraController::SetInfo(const ratchet::camera::CameraController::CameraInfo& info) {
    _position = info.start_position;
    _target = info.target_position;
}

std::shared_ptr<ratchet::camera::Camera> ratchet::camera::CameraController::GetCamera(void) const {
    return this->_camera;
}

Mof::CVector3 ratchet::camera::CameraController::GetCameraPosition(void) const {
    if (_camera) {
        return _camera->GetPosition();
    } // if
    return Mof::CVector3();
}

Mof::CVector3 ratchet::camera::CameraController::GetViewFront(void) const {
    if (_camera) {
        return _camera->GetViewFront();
    } // if
    return Mof::CVector3();
}

float ratchet::camera::CameraController::GetAzimuth(void) const {
    return this->_param.azimuth();
}

float ratchet::camera::CameraController::GetAltitude(void) const {
    return this->_param.altitude();
}

float ratchet::camera::CameraController::GetDistance(void) const {
    return this->_param.distance;
}

float ratchet::camera::CameraController::GetDefaultAzimuth(void) const {
    math::Radian value = 270.0f;
    return value();
}

float ratchet::camera::CameraController::GetDefaultAltitude(void) const {
    math::Radian altitude = 25.0f;
    return altitude();
}

Mof::CVector3 ratchet::camera::CameraController::GetVelocity(void) const {
    return this->_param.velocity;
}

Mof::CVector3 ratchet::camera::CameraController::GetPreviousPosition(void) const {
    return this->_previous_position;
}

bool ratchet::camera::CameraController::IsUpdatePositionFlag(void) const {
    return this->_update_position_flag;
}

void ratchet::camera::CameraController::AddAzimuth(float degree) {
    this->_param.azimuth += degree;
}

void ratchet::camera::CameraController::AddAltitude(float degree) {
    _param.altitude += degree;
    if (_param.altitude <= -5.0f) {
        _param.altitude = -5.0f;
    } // if
    if (_param.altitude >= 45.0f) {
        _param.altitude = 45.0f;
    } // if
}

bool ratchet::camera::CameraController::Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info) {
    return true;
}

bool ratchet::camera::CameraController::Release(void) {
    _camera.reset();
    return true;
}

bool ratchet::camera::CameraController::RegisterGlobalCamera(void) {
    _ASSERT_EXPR(!_manager.expired(), L"–³Œø‚Èƒ|ƒCƒ“ƒ^‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚·");
    _manager.lock()->RegisterGlobalCamera(_camera);
    return true;
}