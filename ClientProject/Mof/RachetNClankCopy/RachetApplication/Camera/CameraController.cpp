#include "CameraController.h"


std::weak_ptr<rachet::CameraManager> rachet::CameraController::_manager;


void rachet::CameraController::SetCameraManager(const std::shared_ptr<rachet::CameraManager>& ptr) {
    _manager = ptr;
}

rachet::CameraController::CameraController() :
    _camera(),
    _position(),
    _target(),
    _preview_position() {
}

rachet::CameraController::~CameraController() {
}

rachet::CameraController::operator bool(void) const {
    return _camera.get();
}

void rachet::CameraController::SetCamera(const std::shared_ptr<rachet::Camera>& ptr) {
    this->_camera = ptr;
}

/*
void rachet::CameraController::SetCameraPosition(Mof::CVector3 pos) {
    this->_position = pos;
}

void rachet::CameraController::SetCameraTarget(Mof::CVector3 pos) {
    this->_target = pos;
}
*/

void rachet::CameraController::SetDistance(float value) {
    this->_param.distance = value;
}

void rachet::CameraController::SetAzimuth(float degree) {
    this->_param.azimuth = degree;
}

void rachet::CameraController::SetAltitude(float degree) {
    this->_param.altitude = degree;
}

void rachet::CameraController::SetSpring(float value) {
    this->_param.spring = value;
}

void rachet::CameraController::SetDumping(float value) {
    this->_param.dumping = value;
}

void rachet::CameraController::SetInfo(const rachet::CameraController::CameraInfo& info) {
    _position = info.start_position;
    _target = info.target_position;
}

std::shared_ptr<rachet::Camera> rachet::CameraController::GetCamera(void) const {
    return this->_camera;
}

Mof::CVector3 rachet::CameraController::GetCameraPosition(void) const {
    if (_camera) {
        return _camera->GetPosition();
    } // if
    return Mof::CVector3();
}

Mof::CVector3 rachet::CameraController::GetViewFront(void) const {
    if (_camera) {
        return _camera->GetViewFront();
    } // if
    return Mof::CVector3();
}

float rachet::CameraController::GetAzimuth(void) const {
    return this->_param.azimuth();
}

float rachet::CameraController::GetAltitude(void) const {
    return this->_param.altitude();
}

float rachet::CameraController::GetDefaultAzimuth(void) const {
    math::Radian value = 270.0f;
    return value();
}

float rachet::CameraController::GetDefaultAltitude(void) const {
    math::Radian altitude = 25.0f;
    return altitude();
}

Mof::CVector3 rachet::CameraController::GetVelocity(void) const {
    return this->_param.velocity;
}

Mof::CVector3 rachet::CameraController::GetPreviewPosition(void) const {
    return this->_preview_position;
}

void rachet::CameraController::AddAzimuth(float degree) {
    this->_param.azimuth += degree;
}

void rachet::CameraController::AddAltitude(float degree) {
    _param.altitude += degree;
    if (_param.altitude <= -5.0f) {
        _param.altitude = -5.0f;
    } // if
    if (_param.altitude >= 45.0f) {
        _param.altitude = 45.0f;
    } // if
}

bool rachet::CameraController::Update(float delta_time, const rachet::CameraController::CameraInfo& info) {
    return true;
}

bool rachet::CameraController::Release(void) {
    _camera.reset();
    return true;
}

bool rachet::CameraController::RegisterGlobalCamera(void) {
    _ASSERT_EXPR(!_manager.expired(), L"–³Œø‚Èƒ|ƒCƒ“ƒ^‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚·");
    _manager.lock()->RegisterGlobalCamera(_camera);
    return true;
}