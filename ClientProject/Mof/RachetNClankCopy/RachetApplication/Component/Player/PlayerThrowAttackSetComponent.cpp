#include "PlayerThrowAttackSetComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"
#include "PlayerMoveComponent.h"
#include "PlayerWeaponComponent.h"



my::PlayerThrowAttackSetComponent::PlayerThrowAttackSetComponent(int priority) :
    super(priority) ,
    _motion_state_com() {
}

my::PlayerThrowAttackSetComponent::PlayerThrowAttackSetComponent(const PlayerThrowAttackSetComponent& obj) :
    super(obj),
    _motion_state_com() {
}

my::PlayerThrowAttackSetComponent::~PlayerThrowAttackSetComponent() {
}

std::string my::PlayerThrowAttackSetComponent::GetType(void) const {
    return "PlayerThrowAttackSetComponent";
}

std::string_view my::PlayerThrowAttackSetComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackSetState;
}

bool my::PlayerThrowAttackSetComponent::Initialize(void) {
    super::Initialize();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::PlayerThrowAttackSetComponent::Update(float delta_time) {
    return true;
}

bool my::PlayerThrowAttackSetComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerThrowAttackSetComponent::Clone(void) {
    return std::make_shared<my::PlayerThrowAttackSetComponent>(*this);
}

bool my::PlayerThrowAttackSetComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionThrowAttackSetState);
    } // if
    /*
    _next_reserve = false;
    if (auto move_com = _move_com.lock()) {
        Mof::CVector2 in; float move_angle;
        float move_speed = 15.0f; float angular_speed = 0.0f; float ideal_angle = super::GetOwner()->GetRotate().y;
        if (move_com->AquireInputData(in, move_angle)) {
            in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
            angular_speed = 15.0f; ideal_angle = std::atan2(-in.y, in.x) - math::kHalfPi;
        } // if
        move_com->Move(move_speed, angular_speed, ideal_angle);
    } // if
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Activate();
    } // if
    */
    return true;
}

bool my::PlayerThrowAttackSetComponent::End(void) {
    super::End();
    /*
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    */
    return true;
}