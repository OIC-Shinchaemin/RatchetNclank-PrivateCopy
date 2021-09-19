#include "EnemyViewEvent.h"

#include "../Gamepad.h"


ratchet::event::EnemyViewEvent::EnemyViewEvent() :
    super(),
    _camera(std::make_shared<ratchet::camera::Camera>()),
    _camera_controller(std::make_shared<ratchet::camera::AutoCameraController>(9.0f))
    //_scene(),
    //_skip_time_set(0.6f),
    //_skip_reserve_timer() 
{
    _camera_controller->SetCamera(_camera);
    _camera->Initialize();
    _camera->Update();
    //_skip_reserve_timer.Initialize(_skip_time_set, false);

    std::vector<Mof::CVector3> control_points_target = {
        Mof::CVector3(56.0f, -30.0f, 26.0f),
        Mof::CVector3(42.0f, -30.0f, 34.0f),
        Mof::CVector3(56.0f, -30.0f, 83.0f),
        Mof::CVector3(95.0f, -30.0f, 178.0f),
        Mof::CVector3(141.0f,-30.0f, 125.0f),
        Mof::CVector3(141.0f,-30.0f, 92.0f),
        Mof::CVector3(193.0f,-30.0f, 55.0f),
        Mof::CVector3(197.0f,-31.0f, 0.0f),
        Mof::CVector3(138.0f,-31.0f, 25.0f),
        Mof::CVector3(108.0f,-31.0f, 25.0f),
        Mof::CVector3(108.0f,-31.0f, 25.0f),
        Mof::CVector3(108.0f,-31.0f, 25.0f),
        Mof::CVector3(108.0f,-31.0f, 25.0f),
    };
    std::vector<Mof::CVector3> control_points_position = {
        Mof::CVector3(60.0f, -15.0f, 17.0f),
        Mof::CVector3(60.0f, -15.0f, 17.0f),
        Mof::CVector3(60.0f, -15.0f, 17.0f),
        Mof::CVector3(50.0f, -15.0f, 57.0f),
        Mof::CVector3(41.0f, -15.0f, 72.0f),
        Mof::CVector3(84.0f, -15.0f, 156.0f),
        Mof::CVector3(124.0f,-15.0f, 146.0f),
        Mof::CVector3(140.0f,-15.0f, 110.0f),
        Mof::CVector3(155.0f,-15.0f, 30.0f),
        Mof::CVector3(136.0f,-15.0f, 26.0f),
        Mof::CVector3(106.0f,-15.0f, 26.0f),
        Mof::CVector3(86.0f, -15.0f, 26.0f),
        Mof::CVector3(56.0f, -15.0f, 26.0f),
    };

    _camera_controller->TimerReset(9.0f);
    _camera_controller->RegisterCameraPositionControllPoint(control_points_position);
    _camera_controller->RegisterCameraTargetControllPoint(control_points_target);
}

ratchet::event::EnemyViewEvent::~EnemyViewEvent() {
}

ratchet::event::EnemyViewEvent::CameraObservable* ratchet::event::EnemyViewEvent::GetCameraObservable(void) {
    return &this->_camera_subject;
}

bool ratchet::event::EnemyViewEvent::Initialize(void) {
    _camera_controller->RegisterGlobalCamera();
    return true;
}

bool ratchet::event::EnemyViewEvent::Update(float delta_time) {
    //if (auto scene = _scene.lock()) {
    //	if (scene->GetState() == scene::Scene::State::Pause) {
    //		return true;
    //	} // if
    //} // if
    //// 一定時間経過で削除リクエストを通知
    //if (::g_pInput->IsKeyPush(MOFKEY_RETURN) ||
    //	::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_START)) {
    //	if (_skip_reserve) {
    //		_camera_controller->ForceTick(_camera_controller->GetTimeMax());
    //	} // if
    //	_skip_reserve = true;
    //} // if

    //if (_skip_reserve_timer.Tick(delta_time)) {
    //	_skip_reserve = false;
    //	_skip_reserve_timer.Initialize(_skip_time_set, false);
    //} // if


    auto camera_info = ratchet::camera::CameraController::CameraInfo();
    _camera_controller->Update(delta_time, camera_info);

    if (_camera_controller->IsCompleted()) {
        auto message = EnemyViewEventMessage();
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