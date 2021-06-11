#include "PointCameraController.h"


ratchet::PointCameraController::PointCameraController() :
    super(),
    _ideal_position() {
    _param.azimuth = 0.0f;
    _param.altitude = 0.0f;
    _param.distance = 1.0f;
    _param.spring = 25.0f;
    _param.dumping = std::sqrtf(_param.spring) * 1.5f;
}

ratchet::PointCameraController::~PointCameraController() {
}

void ratchet::PointCameraController::SetInfo(const ratchet::CameraController::CameraInfo& info) {
    super::_position = info.start_position;
    super::_target = info.target_position;
    _ideal_position = Mof::CVector3();
}

bool ratchet::PointCameraController::Update(float delta_time, const ratchet::CameraController::CameraInfo& info) {
    auto& [azimuth, altitude, distance, spring, dumping, velocity] = _param;
    
    auto displace = _position - _ideal_position;
    auto accel = (displace * (-spring)) - (velocity * dumping);

    velocity += accel * delta_time;
    _position += velocity * delta_time;

    _camera->SetTarget(_target);
    _camera->SetPosition(_position);
    return true;
}