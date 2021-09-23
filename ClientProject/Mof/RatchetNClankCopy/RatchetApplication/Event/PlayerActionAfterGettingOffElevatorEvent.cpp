#include "PlayerActionAfterGettingOffElevatorEvent.h"

#include "EventReferenceTable.h"
#include "../Actor/Actor.h"
#include "../Actor/Character/Player.h"
#include "../Component/ActionStateComponent.h"
#include "../Component/MotionStateComponent.h"
#include "../Component/MotionComponent.h"
#include "../Component/Player/PlayerMoveComponent.h"
#include "../Component/Player/PlayerJumpSetComponent.h"
#include "../Component/Player/PlayerJumpUpComponent.h"
#include "../Component/Player/PlayerJumpDownComponent.h"
#include "../State/PlayerActionStateDefine.h"
#include "../State/PlayerMotionStateDefine.h"
#include "PlayerActionAfterGettingOffElevatorEvent.h"


ratchet::event::PlayerActionAfterGettingOffElevatorEvent::PlayerActionAfterGettingOffElevatorEvent() :
    super(),
    _active(),
    _start_time_set(1.6f),
    _time_set(2.0f),
    _start_timer(),
    _timer(),
    _front_angle(0.0f),
    _add_jump(false),
    _current_state(),
    _prev_state(),

    _default_jump_set_first_speed(6.0f),
    _default_jump_up_move_speed(2.4f),
    _default_jump_up_angular_speed(3.3f),
    _default_jump_up_gravity(1.8f) {
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
        auto state = player->GetComponent<ratchet::component::ActionStateComponent>();
        auto action = player->GetComponent<ratchet::component::ActionComponent>();

        state->ChangeState(state::PlayerActionStateType::kPlayerActionJumpSetState);

        auto jump_set_com = std::dynamic_pointer_cast<component::player::action::PlayerJumpSetComponent> (action->GetChildren().at("PlayerJumpSetComponent"));
        auto jump_up_com = std::dynamic_pointer_cast<component::player::action::PlayerJumpUpComponent> (action->GetChildren().at("PlayerJumpUpComponent"));
        auto jump_down_com = std::dynamic_pointer_cast<component::player::action::PlayerJumpDownComponent> (action->GetChildren().at("PlayerJumpDownComponent"));

        //jump_up_com->force_move_radian_angle = player->GetRotate().y - math::kHalfPi;
        //jump_up_com->force_move_radian_angle = -math::kHalfPi;
        jump_up_com->force_move_radian_angle = player->GetRotate().y - (math::kHalfPi * 0.5f);
        jump_set_com->SetJumpSpeedFirst(18.0f);
        jump_up_com->SetMoveSpeed(10.0f);
        jump_up_com->SetAngularSpeed(2.0f);
        jump_up_com->SetGravityDown(0.0f);
        jump_set_com->Start();
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
        auto state = player->GetComponent < ratchet::component::player::PlayerStateComponent>();
        auto jump_set_com = std::dynamic_pointer_cast<component::player::action::PlayerJumpSetComponent> (action->GetChildren().at("PlayerJumpSetComponent"));
        auto jump_up_com = std::dynamic_pointer_cast<component::player::action::PlayerJumpUpComponent> (action->GetChildren().at("PlayerJumpUpComponent"));
        auto jump_down_com = std::dynamic_pointer_cast<component::player::action::PlayerJumpDownComponent> (action->GetChildren().at("PlayerJumpDownComponent"));
    } // if
    if (_timer.Tick(delta_time)) {
        auto player = event::EventReferenceTable::Singleton().Get<std::shared_ptr<ratchet::actor::character::Player>>("player");
        player->Activate();

        auto camera = player->GetComponent<ratchet::component::CameraComponent>();
        camera->GetCameraController()->GetService()->SetAzimuth(235);
        camera->GetCameraController()->GetService()->RegisterGlobalCamera();

        auto action = player->GetComponent<ratchet::component::ActionComponent>();
        auto jump_set_com = std::dynamic_pointer_cast<component::player::action::PlayerJumpSetComponent> (action->GetChildren().at("PlayerJumpSetComponent"));
        auto jump_up_com = std::dynamic_pointer_cast<component::player::action::PlayerJumpUpComponent> (action->GetChildren().at("PlayerJumpUpComponent"));

        //auto move_com = std::dynamic_pointer_cast<component::player::action::PlayerMoveComponent> (action->GetChildren().at("PlayerMoveComponent"));
        //move_com->InputMoveAngularVelocity(math::ToRadian(235), 2.0f);

        jump_set_com->SetJumpSpeedFirst(_default_jump_set_first_speed);
        jump_up_com->SetMoveSpeed(_default_jump_up_move_speed);
        jump_up_com->SetAngularSpeed(_default_jump_up_angular_speed);
        jump_up_com->SetGravityDown(_default_jump_up_gravity);
        jump_up_com->force_move_radian_angle->reset();


        auto ptr = super::GetSubject();
        ptr->Notify("DeleteRequest", shared_from_this());
        return true;
    } // if
    return false;
}