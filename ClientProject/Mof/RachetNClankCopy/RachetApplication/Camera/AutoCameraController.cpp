#include "AutoCameraController.h"


my::AutoCameraController::AutoCameraController() :
    super(),
    _time(6.0f),
    _timer(),
    _bezier_curve_animation_position(_time),
    _bezier_curve_animation_target(_time) {

    _timer.Initialize(_time, true);
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

void my::AutoCameraController::AddObserver(const std::shared_ptr<my::Observer<const my::CameraController::CameraInfo&>>& ptr) {
    Observable::AddObserver(ptr);
}

bool my::AutoCameraController::Update(float delta_time) {
    if (_timer.Tick(delta_time)) {
        auto info = super::CameraInfo();
        auto pos = _bezier_curve_animation_position.CalculatePointPosition(_timer());
        info.position = pos;
        info.target = math::vec3::kZero;
        Observable::Notify(info);
    } // if

    auto pos = _bezier_curve_animation_position.CalculatePointPosition(_timer());
    _camera->SetPosition(pos);
    _camera->SetTarget(Mof::CVector3(5.0f, 0.0f, -5.0f));
    return true;
}