#include "EnemyViewEvent.h"


ratchet::event::EnemyViewEvent::EnemyViewEvent() :
    super(),
    _camera(std::make_shared<ratchet::camera::Camera>()),
    _camera_controller(std::make_shared<ratchet::camera::AutoCameraController>()),
    _player_camera_controller() {
    _camera->Initialize();
    _camera->Update();
    _camera_controller->SetCamera(_camera);
}

ratchet::event::EnemyViewEvent::~EnemyViewEvent() {
}

ratchet::event::EnemyViewEvent::CameraObservable* ratchet::event::EnemyViewEvent::GetCameraObservable(void) {
    return &this->_camera_subject;
}

void ratchet::event::EnemyViewEvent::SetStartPosition(Mof::CVector3 pos) {
    this->_start_position = pos;
}

void ratchet::event::EnemyViewEvent::SetPlayerCamera(base::core::ServiceLocator<ratchet::camera::CameraController>* ptr) {
    this->_player_camera_controller = ptr;
}

bool ratchet::event::EnemyViewEvent::Initialize(void) {
    auto p = _player_camera_controller->GetService()->GetCameraPosition();
    auto player_camera = _player_camera_controller->GetService();
    Mof::CVector3 target = Mof::CVector3(65.0, -30.0f, 82.0f);
    Mof::CVector3 dir = target - p;
    dir.y = 0.0f;
    dir.Normal(dir);

    std::vector<Mof::CVector3> control_points_target = {
        target + Mof::CVector3(0.0f, 0.0f, 1.0f) * dir,

        target + Mof::CVector3(0.0f, 0.0f, 1.0f) * dir,
        target + Mof::CVector3(0.0f, 0.0f, 1.0f) * dir,
        target + Mof::CVector3(0.0f, 0.0f,  60.0f) * dir,
        target + Mof::CVector3(0.0f, 0.0f,  60.0f) * dir,
        target + Mof::CVector3(0.0f, 10.0f, 60.0f) * dir,
    };
    std::vector<Mof::CVector3> control_points_position = {
        p ,

        p + Mof::CVector3(0.0f, 0.0f, 1.0f) * dir,
        p + Mof::CVector3(0.0f, 0.0f, 1.0f) * dir,
        p + Mof::CVector3(0.0f, 0.0f,  60.0f) * dir,
        p + Mof::CVector3(0.0f, 0.0f,  60.0f) * dir,
        p + Mof::CVector3(0.0f, 20.0f, 60.0f) * dir + Mof::CVector3(0.0f, 10.0f, 0.0f),
    };

    _camera_controller->TimerReset(6.0f);
    _camera_controller->RegisterCameraPositionControllPoint(control_points_position);
    _camera_controller->RegisterCameraTargetControllPoint(control_points_target);
    _camera_controller->RegisterGlobalCamera();
    _camera->SetPosition(p);
    _camera->SetTarget(target);
    _camera->Update();
    return true;
}

bool ratchet::event::EnemyViewEvent::Update(float delta_time) {
    auto camera_info = ratchet::camera::CameraController::CameraInfo();
    _camera_controller->Update(delta_time, camera_info);

    
    if (_camera_controller->IsCompleted()) {
        auto message = EnemyViewEventEndMessage();
        message.end = true;
        _enemy_view_event_message_subject.Notify(message);

        auto info = ratchet::camera::CameraController::CameraInfo();
        info.start_position = _camera_controller->GetCameraPosition();
        info.target_position = math::vec3::kZero;
        _camera_subject.Notify(info);
        auto ptr = super::GetSubject();
        ptr->Notify("DeleteRequest", shared_from_this());
    } // if
    return true;
}