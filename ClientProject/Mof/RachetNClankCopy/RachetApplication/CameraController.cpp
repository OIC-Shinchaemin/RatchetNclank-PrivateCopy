#include "CameraController.h"

#include "My/Core/Define.h"
#include "Camera.h"
#include "Character.h"


void my::CameraController::UpdateCameraPosition(const std::shared_ptr<my::Camera>& camera) {
    camera->SetTarget(_target);

    auto offset = this->SphericalToCartesian(_distance, _azimuth(), _altitude());
    auto ideal_pos = _target + offset;

    auto displace = _position - ideal_pos;
    auto accel = (displace * (-kSpring)) - (_velocity * kDumping);

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

my::CameraController::CameraController() :
    kSpring (50.0f),
    kDumping(std::sqrt(kSpring) * 2.0f),
    _camera(),
    _position(),
    _target(),
    _distance(5.0f),
    _azimuth(270.0f),
    _altitude(this->GetDefaultAltitude()),
    _velocity() {
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

Mof::CVector3 my::CameraController::GetCameraPosition(void) const {
    if (auto camera = _camera.lock()) {
        return camera->GetPosition();
    } // if
    return Mof::CVector3();
}

Mof::CVector3 my::CameraController::GetViewFront(void) const {
    if (_camera.expired()) {
        return Mof::CVector3();
    } // if
    return _camera.lock()->GetViewFront();
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
    math::Radian altitude = 5.0f;
    return altitude();
}

Mof::CVector3 my::CameraController::GetVelocity(void) const {
    return this->_velocity;
}

void my::CameraController::AddAzimuth(float degree) {
    this->_azimuth += degree;
}

void my::CameraController::AddAltitude(float degree) {
    this->_altitude += degree;
    if (_altitude <= -5.0f) {
        _altitude = -5.0f;
    } // if
    if (_altitude >= 45.0f) {
        _altitude = 45.0f;
    } // if

}

bool my::CameraController::HasValidCamara(void) const {
    return !_camera.expired();
}

bool my::CameraController::Update(void) {
    if (_camera.expired()) {
        return false;
    } // if
    auto camera = _camera.lock();
    this->UpdateCameraPosition(camera);
    return true;
}