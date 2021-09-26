#include "StageViewEvent.h"

#include "../Gamepad.h"


ratchet::event::StageViewEvent::StageViewEvent() :
    super(),
    _stage_view_camera(std::make_shared<ratchet::camera::Camera>()),
    _stage_view_camera_controller(std::make_shared<ratchet::camera::AutoCameraController>()),
    _scene(),
    _text_system(),
    _skip_reserve(false),
    _skip_time_set(0.6f),
    _skip_reserve_timer() {
    _stage_view_camera_controller->SetCamera(_stage_view_camera);
    _stage_view_camera->Initialize();
    _stage_view_camera->Update();
    _skip_reserve_timer.Initialize(_skip_time_set, false);


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
    std::vector<Mof::CVector3> control_points_target = {
        Mof::CVector3(5.0f, 0.0f, -5.0f),
        Mof::CVector3(5.0f, 0.0f, -5.0f),
        Mof::CVector3(5.0f, 0.0f, -5.0f),
        Mof::CVector3(5.0f, 0.0f, -5.0f),
        Mof::CVector3(5.0f, 0.0f, -5.0f),
        Mof::CVector3(5.0f, 0.0f, -5.0f),
        Mof::CVector3(5.0f, 0.0f, -5.0f),
        Mof::CVector3(5.0f, 0.0f, -5.0f),
        Mof::CVector3(5.0f, 0.0f, -5.0f),
        Mof::CVector3(5.0f, 0.0f, -5.0f),
        Mof::CVector3(5.0f, 0.0f, -5.0f),
        Mof::CVector3(5.0f, 0.0f, -5.0f),
        Mof::CVector3(5.0f, 0.0f, -5.0f),
        Mof::CVector3(5.0f, 0.0f, -5.0f),
    };

    _stage_view_camera_controller->RegisterCameraPositionControllPoint(control_points_position);
    _stage_view_camera_controller->RegisterCameraTargetControllPoint(control_points_target);
}

ratchet::event::StageViewEvent::~StageViewEvent() {
}

ratchet::event::StageViewEvent::CameraObservable* ratchet::event::StageViewEvent::GetCameraObservable(void) {
    return &this->_camera_subject;
}

void ratchet::event::StageViewEvent::SetGameScene(const std::shared_ptr<ratchet::scene::Scene>& ptr) {
    this->_scene = ptr;
}

void ratchet::event::StageViewEvent::SetTextSystem(const std::shared_ptr<ratchet::game::gamesystem::text::TextSystem>& ptr) {
    this->_text_system = ptr;
}

bool ratchet::event::StageViewEvent::Initialize(void) {
    _stage_view_camera_controller->RegisterGlobalCamera();
    return true;
}

bool ratchet::event::StageViewEvent::Update(float delta_time) {
    if (auto scene = _scene.lock()) {
        if (scene->GetState() == scene::Scene::State::Pause) {
            return true;
        } // if
    } // if
    // 一定時間経過で削除リクエストを通知

    if (::g_pInput->IsKeyPush(MOFKEY_RETURN) ||
        ::g_pInput->IsKeyPush(MOFKEY_SPACE) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START)) {
        if (_skip_reserve) {
            _stage_view_camera_controller->ForceTick(_stage_view_camera_controller->GetTimeMax());
        } // if
        _skip_reserve = true;
    } // if

    if (_skip_reserve_timer.Tick(delta_time)) {
        _skip_reserve = false;
        _skip_reserve_timer.Initialize(_skip_time_set, false);
    } // if


    auto camera_info = ratchet::camera::CameraController::CameraInfo();
    _stage_view_camera_controller->Update(delta_time, camera_info);

    if (_stage_view_camera_controller->IsCompleted()) {
        auto message = StageViewEventMessage();
        message.end = true;
        _stage_view_event_message_subject.Notify(message);

        auto info = ratchet::camera::CameraController::CameraInfo();
        info.start_position = _stage_view_camera_controller->GetCameraPosition();
        info.target_position = math::vec3::kZero;
        _camera_subject.Notify(info);
        auto ptr = super::GetSubject();
        ptr->Notify("DeleteRequest", shared_from_this());
    } // if
    return true;
}