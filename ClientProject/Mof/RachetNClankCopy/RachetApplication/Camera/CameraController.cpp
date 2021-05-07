#include "CameraController.h"

#include "My/Core/Define.h"
#include "My/Core/Utility.h"


std::weak_ptr<my::CameraManager> my::CameraController::_manager;


void my::CameraController::UpdateCameraPosition(const std::shared_ptr<my::Camera>& camera) {
    camera->SetTarget(_target);

    auto offset = this->SphericalToCartesian(_distance, _azimuth(), _altitude());
    auto ideal_pos = _target + offset;

    auto displace = _position - ideal_pos;
    auto accel = (displace * (-_spring)) - (_velocity * _dumping);

    _velocity += accel * def::kDeltaTime;
    _position += _velocity * def::kDeltaTime;

    camera->SetPosition(_position);
}

Mof::CVector3 my::CameraController::SphericalToCartesian(Mof::CVector3 spherical) const {
    return this->SphericalToCartesian(spherical.x, spherical.y, spherical.z);
}

Mof::CVector3 my::CameraController::SphericalToCartesian(float distance, float azimuth, float altitude) const {
    float x = distance * std::cosf(azimuth) * std::sinf(altitude - math::kHalfPi);
    float y = distance * std::sinf(azimuth) * std::sinf(altitude - math::kHalfPi);
    float z = distance * std::cosf(altitude - math::kHalfPi);
    return Mof::CVector3(x, z, -y);
}

void my::CameraController::SetCameraManager(const std::shared_ptr<my::CameraManager>& ptr) {
    _manager = ptr;
}

my::CameraController::CameraController() :
    _spring(50.0f),
    _dumping(std::sqrt(_spring) * 2.0f),
    _camera(),
    _position(),
    _target(),
    _distance(8.0f),
    _azimuth(270.0f),
    _altitude(this->GetDefaultAltitude()),
    _velocity(),
    _preview_position() {
}

my::CameraController::~CameraController() {
}

void my::CameraController::SetCamera(const std::shared_ptr<my::Camera>& ptr) {
    this->_camera = ptr;
}

void my::CameraController::SetCameraPosition(Mof::CVector3 pos) {
    this->_position = pos;
}

void my::CameraController::SetCameraTarget(Mof::CVector3 pos) {
    this->_target = pos;
}

void my::CameraController::SetDistance(float value) {
    this->_distance = value;
}

void my::CameraController::SetAzimuth(float degree) {
    this->_azimuth = degree;
}

void my::CameraController::SetAltitude(float degree) {
    this->_altitude = degree;
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
    return _azimuth();
}

float my::CameraController::GetAltitude(void) const {
    return _altitude();
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
    return this->_velocity;
}

Mof::CVector3 my::CameraController::GetPreviewPosition(void) const {
    return this->_preview_position;
}

void my::CameraController::AddAzimuth(float degree) {
    this->_azimuth += degree;
}

void my::CameraController::AddAltitude(float degree) {
    this->_altitude += degree;
    if (_altitude <= -15.0f) {
        _altitude = -15.0f;
    } // if
    if (_altitude >= 45.0f) {
        _altitude = 45.0f;
    } // if
}

bool my::CameraController::HasValidCamara(void) const {
    return _camera.get();
}

bool my::CameraController::Update(void) {
    _preview_position = _position;
    this->UpdateCameraPosition(_camera);
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