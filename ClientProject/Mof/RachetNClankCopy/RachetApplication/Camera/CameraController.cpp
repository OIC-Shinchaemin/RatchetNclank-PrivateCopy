#include "CameraController.h"


std::weak_ptr<my::CameraManager> my::CameraController::_manager;


void my::CameraController::SetCameraManager(const std::shared_ptr<my::CameraManager>& ptr) {
    _manager = ptr;
}

my::CameraController::CameraController() :
    _camera(),
    _position(),
    _target(),
    _preview_position() {
}

my::CameraController::~CameraController() {
}

my::CameraController::operator bool(void) const {
    return _camera.get();
}

void my::CameraController::SetCamera(const std::shared_ptr<my::Camera>& ptr) {
    this->_camera = ptr;
}

/*
void my::CameraController::SetCameraPosition(Mof::CVector3 pos) {
    this->_position = pos;
}

void my::CameraController::SetCameraTarget(Mof::CVector3 pos) {
    this->_target = pos;
}
*/

void my::CameraController::SetDistance(float value) {
    this->_param.distance = value;
}

void my::CameraController::SetAzimuth(float degree) {
    this->_param.azimuth = degree;
}

void my::CameraController::SetAltitude(float degree) {
    this->_param.altitude = degree;
}

void my::CameraController::SetInfo(const my::CameraController::CameraInfo& info) {
    _position = info.start_position;
    _target = info.target_position;
}

std::shared_ptr<my::Camera> my::CameraController::GetCamera(void) const {
    return this->_camera;
}

Mof::CVector3 my::CameraController::GetCameraPosition(void) const {
    if (_camera) {
        return _camera->GetPosition();
    } // if
    return Mof::CVector3();
}

Mof::CVector3 my::CameraController::GetViewFront(void) const {
    if (_camera) {
        return _camera->GetViewFront();
    } // if
    return Mof::CVector3();
}

float my::CameraController::GetAzimuth(void) const {
    return this->_param.azimuth();
}

float my::CameraController::GetAltitude(void) const {
    return this->_param.altitude();
}

float my::CameraController::GetDefaultAzimuth(void) const {
    math::Radian value = 270.0f;
    return value();
}

float my::CameraController::GetDefaultAltitude(void) const {
    math::Radian altitude = 25.0f;
    return altitude();
}

Mof::CVector3 my::CameraController::GetVelocity(void) const {
    return this->_param.velocity;
}

Mof::CVector3 my::CameraController::GetPreviewPosition(void) const {
    return this->_preview_position;
}

void my::CameraController::AddAzimuth(float degree) {
    this->_param.azimuth += degree;
}

void my::CameraController::AddAltitude(float degree) {
    _param.altitude += degree;
    if (_param.altitude <= -5.0f) {
        _param.altitude = -5.0f;
    } // if
    if (_param.altitude >= 45.0f) {
        _param.altitude = 45.0f;
    } // if
}

bool my::CameraController::Update(float delta_time, const my::CameraController::CameraInfo& info) {
    return true;
}

bool my::CameraController::Release(void) {
    _camera.reset();
    return true;
}

bool my::CameraController::RegisterGlobalCamera(void) {
    _ASSERT_EXPR(!_manager.expired(), L"–³Œø‚Èƒ|ƒCƒ“ƒ^‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚·");
    _manager.lock()->RegisterGlobalCamera(_camera);
    return true;
}