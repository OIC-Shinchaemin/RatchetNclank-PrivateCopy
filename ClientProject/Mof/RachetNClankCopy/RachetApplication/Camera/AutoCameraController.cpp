#include "AutoCameraController.h"


my::AutoCameraController::AutoCameraController() :
    super(),
    _time(5.0f),
    _timer(),
    _bezier_curve_animation_position(_time) ,
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
    Mof::CVector3(80.0f, 12.0f, -5.0f),
    };

    _bezier_curve_animation_position.Reserve(control_points_position.size());
    for (auto& position : control_points_position) {
        _bezier_curve_animation_position.AddControlPoint(position);
    } // for
}

my::AutoCameraController::~AutoCameraController() {
}

bool my::AutoCameraController::Update(float delta_time) {
    if (_timer.Tick(delta_time)) {
        puts("");
    } // if

    auto pos = _bezier_curve_animation_position.CalculatePointPosition(_timer());
    _camera->SetPosition(pos);
    _camera->SetTarget(math::vec3::kZero);
    return true;
}