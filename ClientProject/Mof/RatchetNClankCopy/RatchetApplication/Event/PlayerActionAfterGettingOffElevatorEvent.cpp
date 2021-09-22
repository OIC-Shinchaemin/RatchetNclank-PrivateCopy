#include "PlayerActionAfterGettingOffElevatorEvent.h"

#include "EventReferenceTable.h"
#include "../Actor/Actor.h"
#include "../Actor/Character/Player.h"
#include "../Component/ActionStateComponent.h"
#include "../Component/MotionStateComponent.h"
#include "../Component/MotionComponent.h"
#include "../Component/Player/PlayerMoveComponent.h"
#include "../Component/Player/PlayerJumpSetComponent.h"
#include "../State/PlayerActionStateDefine.h"
#include "../State/PlayerMotionStateDefine.h"
#include "PlayerActionAfterGettingOffElevatorEvent.h"


ratchet::event::PlayerActionAfterGettingOffElevatorEvent::PlayerActionAfterGettingOffElevatorEvent() :
	super(),
	_active(),
	_start_time_set(1.0f),
	_time_set(2.0f),
	_start_timer(),
	_timer(),
	_front_angle(0.0f) {
	_start_timer = base::core::Timer();
	_start_timer.value().Initialize(_start_time_set, false);
	_timer.Initialize(_time_set, false);
}

ratchet::event::PlayerActionAfterGettingOffElevatorEvent::~PlayerActionAfterGettingOffElevatorEvent() {
}

void ratchet::event::PlayerActionAfterGettingOffElevatorEvent::OnNotify(const ratchet::event::EnemyViewEventEndMessage& message) {
	_active = true;

	if (event::EventReferenceTable::Singleton().Exist("player")) {
		auto player = event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::actor::character::Player>>("player");
		auto camera = player->GetComponent<ratchet::component::CameraComponent>();
		camera->GetCameraController()->GetService()->SetAzimuth(250);
		//auto action = player->GetComponent<ratchet::component::ActionStateComponent>();
		//action->ChangeState(state::PlayerActionStateType::kPlayerActionJumpSetState);
		//_start_camera_angle = camera->GetCameraController()->GetService()->GetAzimuth();
	} // if
}

bool ratchet::event::PlayerActionAfterGettingOffElevatorEvent::Initialize(void) {
	return true;
}

bool ratchet::event::PlayerActionAfterGettingOffElevatorEvent::Update(float delta_time) {
	if (!_active) {
		return false;
	} // if
	if (_start_timer.has_value() && _start_timer.value().Tick(delta_time)) {
		_start_timer.reset();
	} // if
	if (_start_timer.has_value()) {
		return false;
	} // if


	if (event::EventReferenceTable::Singleton().Exist("player")) {
		auto player = event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::actor::character::Player>>("player");
		auto action = player->GetComponent<ratchet::component::ActionComponent>();
		auto move_com = std::dynamic_pointer_cast<component::player::action::PlayerMoveComponent> (action->GetChildren().at("PlayerMoveComponent"));
		auto jump_com = std::dynamic_pointer_cast<component::player::action::PlayerJumpSetComponent> (action->GetChildren().at("PlayerJumpSetComponent"));
		//jump_com->Move(4.0f, 4.0f, _front_angle);
		jump_com->SetMoveSpeed(4.0f);
		auto camera = player->GetComponent<ratchet::component::CameraComponent>();
		camera->GetCameraController()->GetService()->SetAzimuth(250);
//		Mof::CVector3Utilities::Lerp();
	} // if

	if (_timer.Tick(delta_time)) {
		return true;
	} // if
	return false;
}