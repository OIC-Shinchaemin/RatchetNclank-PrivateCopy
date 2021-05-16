#include "PlayerThrowAttackComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"
#include "PlayerMoveComponent.h"
#include "PlayerWeaponComponent.h"


my::PlayerThrowAttackComponent::PlayerThrowAttackComponent(int priority) :
    super(priority)
{
}

my::PlayerThrowAttackComponent::PlayerThrowAttackComponent(const PlayerThrowAttackComponent& obj) :
    super(obj)
{
}

my::PlayerThrowAttackComponent::~PlayerThrowAttackComponent() {
}

std::string my::PlayerThrowAttackComponent::GetType(void) const {
    return "PlayerThrowAttackComponent";
}

std::string_view my::PlayerThrowAttackComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackState;
}

bool my::PlayerThrowAttackComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::PlayerThrowAttackComponent::Update(float delta_time) {
    return true;
}

bool my::PlayerThrowAttackComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerThrowAttackComponent::Clone(void) {
    return std::make_shared<my::PlayerThrowAttackComponent>(*this);
}

bool my::PlayerThrowAttackComponent::Start(void) {
    /*
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    _next_reserve = false;
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackOneState);
    } // if
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

bool my::PlayerThrowAttackComponent::End(void) {
    /*
    super::End();
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    */
    return true;
}