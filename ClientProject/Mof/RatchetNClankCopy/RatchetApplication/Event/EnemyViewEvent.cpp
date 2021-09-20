#include "EnemyViewEvent.h"

#include "../Gamepad.h"


ratchet::event::EnemyViewEvent::EnemyViewEvent() :
    super(),
    _camera(std::make_shared<ratchet::camera::Camera>()),
    _camera_controller(std::make_shared<ratchet::camera::AutoCameraController>(9.0f)),
    _player_camera_controller() {
    _camera_controller->SetCamera(_camera);
    _camera->Initialize();
    _camera->Update();
    //_skip_reserve_timer.Initialize(_skip_time_set, false);
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
    auto p = _start_position;
    //auto p = _camera_controller->GetCameraPosition();
    //auto p = ::CGraphicsUtilities::GetCamera()->GetViewPosition();
    //auto t = ::CGraphicsUtilities::GetCamera()->GetTargetPosition();
    //Mof::CVector3 dir = t - p;
    //dir.y = 0.0f;
    //dir.Normal(dir);
    //float angle = _camera_controller->GetAzimuth();
    //auto f = Mof::CVector3(0.0f, _camera_controller->GetAzimuth(), 0.0f);

    auto player_camera = _player_camera_controller->GetService();
    auto c = math::SphericalToCartesian(player_camera->GetDistance(), player_camera->GetAzimuth(), player_camera->GetAltitude());
    std::vector<Mof::CVector3> control_points_target = {
        p + c,
    };
    std::vector<Mof::CVector3> control_points_position = {
        p,
    };

    _camera_controller->TimerReset(4.0f);
    _camera_controller->RegisterCameraPositionControllPoint(control_points_position);
    _camera_controller->RegisterCameraTargetControllPoint(control_points_target);

    //_camera_controller->RegisterGlobalCamera();
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
    //auto angle= CVector3Utilities::Lerp(_camera_info, _camera_info_at, _time);
    //_camera_controller->SetAzimuth(angle.x);
    //_camera_controller->AddAltitude(angle.y);
    //_camera_controller->SetDistance(angle.z);
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