#include "AutoCameraController.h"


my::AutoCameraController::AutoCameraController() :
    super(),
    _time_max(6.0f),
    _time(_time_max),
    _timer(),
    _bezier_curve_animation_position(_time),
    _bezier_curve_animation_target(_time) {

    _timer.Initialize(_time, false, true);
    std::vector<Mof::CVector3> control_points_position = {
    Mof::CVector3(180.0f, 12.0f, 30.0f),
    Mof::CVector3(155.0f, 12.0f, 80.0f),
    Mof::CVector3(150.0f, 12.0f, 125.0f),
    Mof::CVector3(120.0f, 12.0f, 150.0f),
    Mof::CVector3(75.0f, 12.0f, 130.0f),
    Mof::CVector3(55.0f, 12.0f, 85.0f),
    Mof::CVector3(55.0f, 12.0f, 85.0f),
    Mof::CVector3(70.0f, 12.0f, 85.0f),
    Mof::CVector3(75.0f, 12.0f, 5.0f),
    Mof::CVector3(80.0f, 12.0f, -5.0f),
    Mof::CVector3(40.0f, 12.0f, -5.0f),
    Mof::CVector3(10.0f, 12.0f, -5.0f),
    Mof::CVector3(5.0f, 12.0f, -5.0f),
    Mof::CVector3(5.0f, 5.0f, -5.0f),
    };

    _bezier_curve_animation_position.Reserve(control_points_position.size());
    for (auto& position : control_points_position) {
        _bezier_curve_animation_position.AddControlPoint(position);
    } // for
}

my::AutoCameraController::~AutoCameraController() {
}

float my::AutoCameraController::GetTimeMax(void) const {
    return this->_time_max;
}

void my::AutoCameraController::ForceTick(float time) {
    if (_timer.Tick(time)) {
        auto info = super::CameraInfo();
        auto pos = _bezier_curve_animation_position.CalculatePointPosition(_timer());
        info.start_position = pos;
        info.target_position = math::vec3::kZero;
        Observable::Notify(info);
    } // if

}

void my::AutoCameraController::AddObserver(const std::shared_ptr<my::Observer<const my::CameraController::CameraInfo&>>& ptr) {
    Observable::AddObserver(ptr);
}

bool my::AutoCameraController::Update(float delta_time, const my::CameraController::CameraInfo& info) {
    if (_timer.Tick(delta_time)) {
        auto info = super::CameraInfo();
        auto pos = _bezier_curve_animation_position.CalculatePointPosition(_timer());
        info.start_position = pos;
        info.target_position = math::vec3::kZero;
        Observable::Notify(info);
    } // if

    if (_timer() <= _time) {
        auto pos = _bezier_curve_animation_position.CalculatePointPosition(_timer());
        _camera->SetPosition(pos);
        _camera->SetTarget(Mof::CVector3(5.0f, 0.0f, -5.0f));
    } // if
    return true;
}