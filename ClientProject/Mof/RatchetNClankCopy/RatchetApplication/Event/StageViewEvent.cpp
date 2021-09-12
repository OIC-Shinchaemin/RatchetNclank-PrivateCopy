#include "StageViewEvent.h"

#include "../Gamepad.h"


ratchet::event::StageViewEvent::StageViewEvent() :
    super(),
    _stage_view_camera(std::make_shared<ratchet::camera::Camera>()),
    _stage_view_camera_controller(std::make_shared<ratchet::camera::AutoCameraController>()),
    _help_desk(),
    _scene(),
    _text_system(){
    _stage_view_camera_controller->SetCamera(_stage_view_camera);
    _stage_view_camera->Initialize();
    _stage_view_camera->Update();
}

ratchet::event::StageViewEvent::~StageViewEvent() {
}

ratchet::event::StageViewEvent::CameraObservable* ratchet::event::StageViewEvent::GetCameraObservable(void) {
    return &this->_camera_subject;
}

void ratchet::event::StageViewEvent::SetHelpDesk(const std::shared_ptr<ratchet::game::gamesystem::HelpDesk>& ptr) {
    this->_help_desk = ptr;
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
    if (auto scene =_scene.lock()) {
        if (scene->GetState() == scene::Scene::State::Pause) {
            return true;
        } // if
    } // if
    // 一定時間経過で削除リクエストを通知
    if (::g_pInput->IsKeyPush(MOFKEY_SPACE) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START)) {
        _stage_view_camera_controller->ForceTick(_stage_view_camera_controller->GetTimeMax());
    } // if

    auto camera_info = ratchet::camera::CameraController::CameraInfo();
    _stage_view_camera_controller->Update(delta_time, camera_info);
    
    if (_stage_view_camera_controller->IsCompleted()) {
        if (auto help_desk = _help_desk.lock()) {
            help_desk->Show();
        } // if
        auto message = StageViewEventMessage();        
        message.end = true;
        _stage_view_event_message_subject.Notify(message);


        //if (auto text = _text_system.lock()) {
        //    text->Activate();
        //} // if
        //if (auto scene = _scene.lock()) {
        //    scene->SetState(scene::Scene::State::Pause);
        //} // if



        auto info = ratchet::camera::CameraController::CameraInfo();
        info.start_position = _stage_view_camera_controller->GetCameraPosition();
        info.target_position = math::vec3::kZero;
        _camera_subject.Notify(info);
        auto ptr = super::GetSubject();
        ptr->Notify("DeleteRequest", shared_from_this());
    } // if
    return true;
}