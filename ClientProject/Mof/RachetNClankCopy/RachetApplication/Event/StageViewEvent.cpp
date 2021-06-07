#include "StageViewEvent.h"


my::StageViewEvent::StageViewEvent() :
    super(),
    _stage_view_camera(std::make_shared<my::Camera>()),
    _stage_view_camera_controller(std::make_shared<my::AutoCameraController>()) {
    _stage_view_camera_controller->SetCamera(_stage_view_camera);
    _stage_view_camera->Initialize();
    _stage_view_camera->Update();
}

my::StageViewEvent::~StageViewEvent() {
}

my::StageViewEvent::CameraObservable* my::StageViewEvent::GetCameraObservable(void) {
    return &this->_camera_subject;
}

bool my::StageViewEvent::Initialize(void) {
    _stage_view_camera_controller->RegisterGlobalCamera();
    return true;
}

bool my::StageViewEvent::Update(float delta_time) {
    if (::g_pInput->IsKeyPush(MOFKEY_SPACE)) {
        _stage_view_camera_controller->ForceTick(_stage_view_camera_controller->GetTimeMax());
    } // if

    auto camera_info = my::CameraController::CameraInfo();
    _stage_view_camera_controller->Update(delta_time, camera_info);

    if (_stage_view_camera_controller->IsCompleted()) {
        auto info = my::CameraController::CameraInfo();
        info.start_position = _stage_view_camera_controller->GetCameraPosition();
        info.target_position = math::vec3::kZero;
        _camera_subject.Notify(info);
        auto ptr = super::GetSubject();
        ptr->Notify("DeleteRequest", shared_from_this());
    } // if
    return true;
}