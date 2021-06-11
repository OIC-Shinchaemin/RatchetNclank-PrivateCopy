#include "StageViewEvent.h"


ratchet::event::StageViewEvent::StageViewEvent() :
    super(),
    _stage_view_camera(std::make_shared<ratchet::camera::Camera>()),
    _stage_view_camera_controller(std::make_shared<ratchet::camera::AutoCameraController>()) {
    _stage_view_camera_controller->SetCamera(_stage_view_camera);
    _stage_view_camera->Initialize();
    _stage_view_camera->Update();
}

ratchet::event::StageViewEvent::~StageViewEvent() {
}

ratchet::event::StageViewEvent::CameraObservable* ratchet::event::StageViewEvent::GetCameraObservable(void) {
    return &this->_camera_subject;
}

bool ratchet::event::StageViewEvent::Initialize(void) {
    _stage_view_camera_controller->RegisterGlobalCamera();
    return true;
}

bool ratchet::event::StageViewEvent::Update(float delta_time) {
    if (::g_pInput->IsKeyPush(MOFKEY_SPACE)) {
        _stage_view_camera_controller->ForceTick(_stage_view_camera_controller->GetTimeMax());
    } // if

    auto camera_info = ratchet::camera::CameraController::CameraInfo();
    _stage_view_camera_controller->Update(delta_time, camera_info);

    if (_stage_view_camera_controller->IsCompleted()) {
        auto info = ratchet::camera::CameraController::CameraInfo();
        info.start_position = _stage_view_camera_controller->GetCameraPosition();
        info.target_position = math::vec3::kZero;
        _camera_subject.Notify(info);
        auto ptr = super::GetSubject();
        ptr->Notify("DeleteRequest", shared_from_this());
    } // if
    return true;
}