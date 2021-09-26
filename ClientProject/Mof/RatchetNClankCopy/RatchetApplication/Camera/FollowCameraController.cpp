#include "FollowCameraController.h"

#include "../GameDefine.h"


void ratchet::camera::FollowCameraController::UpdateCameraPosition(float delta_time, const std::shared_ptr<ratchet::camera::Camera>& camera) {
    auto& [azimuth, altitude, distance, spring, dumping, velocity] = _param;
    auto offset = math::SphericalToCartesian(distance, azimuth(), altitude());
    auto ideal_pos = _target + offset;

    auto displace = _position - ideal_pos;
    auto accel = (displace * (-spring)) - (velocity * dumping);
    velocity += accel * delta_time;
    _position += velocity * delta_time;

    if (super::_use_spring) {
        camera->SetPosition(_position);
    } // if
    else {
        camera->SetPosition(ideal_pos);
    } // else
}

void ratchet::camera::FollowCameraController::UpdateTargetPosition(float delta_time, const std::shared_ptr<ratchet::camera::Camera>& camera, Mof::CVector3 ideal_position) {
    //static bool a = false;
    //if (::g_pInput->IsKeyPush(MOFKEY_P)) {
    //    a = !a;
    //} // if


    _ideal_target_position = ideal_position;

    //float diff = std::abs(_ideal_target_position.y - _target.y);
    float diff = std::abs(_ideal_target_position.LengthSquare() - _target.Length());
    if (diff > 0.01f) {
        if (!_interpolate_flag) {
            _interpolate_start_position = _target;
        } // if

        _time += delta_time;
        _time = std::clamp(_time, 0.0f, _time_max);
        float nomalized = std::clamp((_time / _time_max), 0.0f, 1.0f);

        _target = CVector3Utilities::Lerp(_interpolate_start_position, _ideal_target_position, nomalized);
        _interpolate_flag = true;
        
        DEBUG_PRINT(" _time = %f _time nomalized = %f \n", _time, nomalized);
        DEBUG_PRINT(" _target.x = %f, _target.y= %f, _target.z= %f \n", _target.x, _target.y, _target.z);
    } // if
    else {
        ::OutputDebugString("! diff \n");
        _interpolate_flag = false;
        _target = _ideal_target_position;
        _time = 0.0f;
    } // else

    camera->SetTarget(_target);
}

ratchet::camera::FollowCameraController::FollowCameraController() :
    super(),
    _enable_interpolate_target_position(false),
    _ideal_target_position(),
    _time(0.0f),
    _time_max(2.0f) {
    _param.distance = 8.0f;
    _param.azimuth = 270.0f;
    _param.altitude = this->GetDefaultAltitude();
    _param.spring = 30.0f;
    _param.dumping = std::sqrtf(_param.spring) * 2.0f;    
}

ratchet::camera::FollowCameraController::~FollowCameraController() {
}

void ratchet::camera::FollowCameraController::SetInterpolateTargetPositionFlag(bool flag) {
    this->_enable_interpolate_target_position = flag;
}

bool ratchet::camera::FollowCameraController::Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info) {
    _previous_position = _camera->GetPosition();
     
    _target = info.target_position;
    _camera->SetTarget(_target);
    //this->UpdateTargetPosition(delta_time, _camera, info.target_position);
    
    if (this->IsUpdatePositionFlag()) {
        this->UpdateCameraPosition(delta_time, _camera);
    } // if
    return true;
}