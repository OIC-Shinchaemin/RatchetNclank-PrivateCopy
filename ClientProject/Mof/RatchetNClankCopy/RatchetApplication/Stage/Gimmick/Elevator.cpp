#include "Elevator.h"

#include "../../Event/EventManager.h"
#include "../../Event/EnemyViewEvent.h"
#include "../../Event/StageViewEvent.h"

void Elevator::EnemyViewEventStart(void) {
    //std::weak_ptr<ratchet::event::EventManager> event;
    if (auto e = _event_manager.lock()) {
        std::shared_ptr<ratchet::event::EnemyViewEvent> view_event;
        view_event = e->CreateGameEvent<ratchet::event::EnemyViewEvent>();
        view_event->SetStartPosition(_player_camera_component.lock()->GetOwner()->GetPosition());
        view_event->SetPlayerCamera(_camera_controller);
        view_event->Initialize();
        view_event->GetCameraObservable()->AddObserver(_player_camera_component.lock());
    } // if
}

Elevator::Elevator(Vector3 end, float request, bool enable, bool collision, StageObjectType type, std::string name, int mesh_no, Vector3 pos, Vector3 scale, Vector3 rotate) :
    GimmickBase(enable, collision, type, name, mesh_no, pos, scale, rotate),
    _start_pos(pos),
    _end_pos(end),
    _request_time(request),
    _now_timer(0.0f),
    _start_flag(false),
    _end_flag(false),
    _preview_position(_start_pos),
    _initial_position(),
    _first_initialized(false),
    _camera_controller(),
    _elevator_arrival_message_subject(),
    _event_manager(),
    _player_camera_component() {
}

Elevator::~Elevator(void) {
}

void Elevator::SetPlayerCamera(base::core::ServiceLocator<ratchet::camera::CameraController>* ptr) {
    this->_camera_controller = ptr;
}

void Elevator::SetEventManager(const std::shared_ptr<ratchet::event::EventManager>& ptr) {
    this->_event_manager = ptr;
}

void Elevator::SetPlayerCameraComponent(const std::shared_ptr<ratchet::component::CameraComponent>& ptr) {
    this->_player_camera_component = ptr;
}

Mof::CVector3 Elevator::GetPreviewPosition(void) const {
    return this->_preview_position;
}

float Elevator::GetRequestTime(void) const {
    return this->_request_time;
}

Mof::CVector3 Elevator::GetMoveValue(void) const {
    return this->GetPosition() - this->GetPreviewPosition();
}

float Elevator::GetVolume(void) const {
    return 4.5f;
}

float Elevator::GetHeight(void) const {
    return 1.0f;
}

Mof::CSphere Elevator::GetStartPositionSphere(void) const {
    return Mof::CSphere(_start_pos, 20.0f);
}

Mof::CSphere Elevator::GetEndPositionSphere(void) const {
    return Mof::CSphere(_end_pos, 20.0f);
}

void Elevator::Initialize(void) {
    _now_timer = 0.0f;
    _start_pos = _position;
    _start_flag = false;
    _end_flag = false;
    if (!_first_initialized) {
        _initial_position = _position;
    } // if
    else {
        _position = _initial_position;
        _start_pos = _initial_position;
    } // else
    _preview_position = _start_pos;
    RefreshWorldMatrix();
    _first_initialized = true;
}

void Elevator::Update(float delta) {
    _preview_position = _position;
    if (!_start_flag) {
        return;
    }

    auto angle = Mof::CVector3();
    auto source = Mof::CVector3();
    auto dest = Mof::CVector3();

    if (_end_flag) {
        _now_timer -= delta;
        source = Mof::CVector3(_camera_angle_start.x, 30.0f, 0.0f);
        dest = Mof::CVector3(250.0f, 30.0f, 0.0f);
    }
    else {
        _now_timer += delta;
        source = Mof::CVector3(_camera_angle_start.x, 30.0f, 0.0f);
        dest = Mof::CVector3(0.0f, 30.0f, 0.0f);
    }
    const float t = std::clamp((_now_timer / _request_time), 0.0f, 1.0f);
    _position = CVector3Utilities::Lerp(_start_pos, _end_pos, t);
    angle = CVector3Utilities::Lerp(source, dest, t);

    _camera_controller->GetService()->SetAzimuth(angle.x);
    _camera_controller->GetService()->SetAltitude(angle.y);

    if (t == 1.0f && !_end_flag) {
        _start_flag = false;
        _end_flag = true;
        auto message = ElevatorArrivalMessage();
        _elevator_arrival_message_subject.Notify(message);
        this->EnemyViewEventStart();
    }
    if (t == 0.0f && _end_flag) {
        _start_flag = false;
        _end_flag = false;
        auto message = ElevatorArrivalMessage();
        _elevator_arrival_message_subject.Notify(message);
    }
    RefreshWorldMatrix();
}

void Elevator::ActionStart(void) {
    if (!_start_flag) {
        _start_flag = true;
        _camera_angle_start.x = _camera_controller->GetService()->GetAzimuth();
        _camera_angle_start.y = _camera_controller->GetService()->GetAltitude();
    }
}

bool Elevator::IsStart(void) const {
    return _start_flag;
}

Vector3 Elevator::GetEndPos(void) const {
    return _end_pos;
}

float Elevator::GetRequest(void) const {
    return _request_time;
}

void Elevator::SetPosition(const Vector3& pos) {
    StageObject::SetPosition(pos);
    _start_pos = pos;
}

void Elevator::SetStageObjectData(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no, Vector3 pos, Vector3 scale, Vector3 rotate) {
    GimmickBase::SetStageObjectData(enable, collision, type, name, mesh_no, pos, scale, rotate);
    SetPosition(pos);
}

#ifdef STAGEEDITOR

float* Elevator::GetStartPosPointer(void) {
    return _start_pos.fv;
}

float* Elevator::GetEndPosPointer(void) {
    return _end_pos.fv;
}

float* Elevator::GetRequestPointer(void) {
    return &_request_time;
}

#endif//STAGEEDITOR
void Elevator::ReInitialize(void) {
}