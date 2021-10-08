#include "AutoCameraController.h"


ratchet::camera::AutoCameraController::AutoCameraController() :
    super(),
    _time_max(6.0f),
    _time(_time_max),
    _timer(),
    _bezier_curve_animation_position(_time),
    _bezier_curve_animation_target(_time) {
    this->TimerReset(_time);
}

ratchet::camera::AutoCameraController::AutoCameraController(float time) :
    super(),
    _time_max(time),
    _time(_time_max),
    _timer(),
    _bezier_curve_animation_position(_time),
    _bezier_curve_animation_target(_time) {
    this->TimerReset(_time);
}

ratchet::camera::AutoCameraController::~AutoCameraController() {
}

float ratchet::camera::AutoCameraController::GetTimeMax(void) const {
    return this->_time_max;
}

bool ratchet::camera::AutoCameraController::IsCompleted(void) const {
    return _time_max <= _timer();
}

void ratchet::camera::AutoCameraController::RegisterCameraPositionControllPoint(std::vector<Mof::CVector3>& points) {
    _bezier_curve_animation_position.Reserve(points.size());
    for (auto& position : points) {
        _bezier_curve_animation_position.AddControlPoint(position);
    } // for
}

void ratchet::camera::AutoCameraController::RegisterCameraTargetControllPoint(std::vector<Mof::CVector3>& points) {
    _bezier_curve_animation_target.Reserve(points.size());
    for (auto& position : points) {
        _bezier_curve_animation_target.AddControlPoint(position);
    } // for
}

void ratchet::camera::AutoCameraController::TimerReset(float time_set) {
    _time = time_set;
    _time_max = time_set;
    _timer.Initialize(_time, false, true);
}

void ratchet::camera::AutoCameraController::ForceTick(float time) {
    if (_timer.Tick(time)) {
        auto info = super::CameraInfo();
        auto pos = _bezier_curve_animation_position.CalculatePointPosition(_timer());
        info.start_position = pos;
        info.target_position = math::vec3::kZero;
    } // if

}
bool ratchet::camera::AutoCameraController::Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info) {
    if (_timer.Tick(delta_time)) {
        auto info = super::CameraInfo();
        auto pos = _bezier_curve_animation_position.CalculatePointPosition(_timer());
        info.start_position = pos;
        info.target_position = math::vec3::kZero;
    } // if

    if (_timer() <= _time) {
        auto pos = _bezier_curve_animation_position.CalculatePointPosition(_timer());
        auto target = _bezier_curve_animation_target.CalculatePointPosition(_timer());
        _camera->SetPosition(pos);
        _camera->SetTarget(target);
    } // if
    return true;
}