#include "Elevator.h"

#include "../../Event/EventManager.h"
#include "../../Event/EventReferenceTable.h"
#include "../../Event/PlayerActionAfterGettingOffElevatorEvent.h"
#include "../../Event/EnemyViewEvent.h"
#include "../../Event/StageViewEvent.h"
#include "../../Actor/Character/Player.h"
#include "../../Component/Player/PlayerMoveComponent.h"


void Elevator::EnemyViewEventStart(void) {
	_event_started = true;
	if (auto e = _event_manager.lock()) {
		auto player_event = e->CreateGameEvent<ratchet::event::PlayerActionAfterGettingOffElevatorEvent>();
		if (ratchet::event::EventReferenceTable::Singleton().Exist("player")) {
			auto player = ratchet::event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::actor::character::Player>>("player");
			player->Sleep();
			player_event->Start();
		} // if
	} // if
	_event_started = true;
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
	_player_camera_component(),
	_player_velocity_component(),
	_event_started(false),
	_player(),
	_cursor_active_timer(),
	_cursor_blinking_timer(),
	_cursor_texture(),
	_cursor_show(false) {
	bool success = _cursor_texture.Load("../Resource/texture/lock_on_cursor/cursor.png");
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

void Elevator::SetPlayer(const std::shared_ptr<ratchet::actor::character::Player>& ptr) {
	this->_player = ptr;
	if (auto player = _player.lock()) {
		this->_player_velocity_component = player->GetComponent<ratchet::component::VelocityComponent>();
	} // if
}

void Elevator::SetShow(bool flag) {
	StageObject::SetShow(flag);
	if (flag) {
		_cursor_blinking_timer.Initialize(0.4f, false);
		_cursor_active_timer.Initialize(5.0f, false);
		_cursor_show = true;
		_cursor_active = true;
	} // of
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
	_cursor_show = false;
	_cursor_active = false;
}

void Elevator::Update(float delta) {
	_preview_position = _position;
	if (!_start_flag) {
		return;
	}


	if (_cursor_active_timer.Tick(delta)) {
		_cursor_active = false;
		_cursor_show = false;
	} // if
	if (_cursor_active) {
		if (_cursor_blinking_timer.Tick(delta)) {
			_cursor_show = !_cursor_show;
		} // if
	} // if



	auto angle = Mof::CVector3();
	auto source = Mof::CVector3();
	auto dest = Mof::CVector3();

	if (_end_flag) {
		_now_timer -= delta;
		source = Mof::CVector3(_camera_angle_start.x, 30.0f, 0.0f);
		dest = Mof::CVector3(180.0f, 20.0f, 0.0f);
		if (auto player = _player.lock()) {
			auto action = player->GetComponent<ratchet::component::ActionComponent>();
			auto move = std::dynamic_pointer_cast <ratchet::component::player::action::PlayerMoveComponent>(action->GetChildren().at("PlayerMoveComponent"));
			move->InputMoveAngularVelocity(math::ToRadian(180.0f), 2.0f);
		} // if

		std::swap(source, dest);
	} // if
	else {
		_now_timer += delta;
		source = Mof::CVector3(_camera_angle_start.x, _camera_angle_start.y, 0.0f);
		dest = Mof::CVector3(250.0f, 30.0f, 0.0f);

		if (auto player = _player.lock()) {
			auto action = player->GetComponent<ratchet::component::ActionComponent>();
			auto move = std::dynamic_pointer_cast <ratchet::component::player::action::PlayerMoveComponent>(action->GetChildren().at("PlayerMoveComponent"));
			move->InputMoveAngularVelocity(math::ToRadian(150.0f), 0.5f);
		} // if

	} // else
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
		if (!_event_started) {
			this->EnemyViewEventStart();
		} // if
	}
	if (t == 0.0f && _end_flag) {
		_start_flag = false;
		_end_flag = false;
		auto message = ElevatorArrivalMessage();
		_elevator_arrival_message_subject.Notify(message);
	}
	RefreshWorldMatrix();
}

void Elevator::Render(void)
{
	//	auto tex = r->Get<std::shared_ptr<Mof::CTexture>>("../Resource/texture/lock_on_cursor/cursor.png");

	if (_cursor_show) {
		auto trans = Mof::CMatrix44();
		auto pos = GetPosition();
		trans.Translation(pos);
		_cursor_texture.Render(::CGraphicsUtilities::GetCamera()->GetBillBoardMatrix() * trans);
	} // if
}

void Elevator::ActionStart(void) {
	if (!_start_flag) {
		_start_flag = true;
		_camera_angle_start.x = math::ToDegree(_camera_controller->GetService()->GetAzimuth());
		_camera_angle_start.y = 30.0f;
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

void Elevator::DebugRender(void) {
	StageObject::DebugRender();
	::CGraphicsUtilities::RenderString(600.0f, 340.0f, "player camera angle = %f", _camera_controller->GetService()->GetAzimuth());
}

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