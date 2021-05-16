#include "PlayerThrowAttackEndComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"
#include "PlayerMoveComponent.h"
#include "PlayerWeaponComponent.h"


my::PlayerThrowAttackEndComponent::PlayerThrowAttackEndComponent(int priority) :
    super(priority) {
}

my::PlayerThrowAttackEndComponent::PlayerThrowAttackEndComponent(const PlayerThrowAttackEndComponent& obj) :
    super(obj) {
}

my::PlayerThrowAttackEndComponent::~PlayerThrowAttackEndComponent() {
}

std::string my::PlayerThrowAttackEndComponent::GetType(void) const {
    return "PlayerThrowAttackEndComponent";
}

std::string_view my::PlayerThrowAttackEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackEndState;
}

bool my::PlayerThrowAttackEndComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::PlayerThrowAttackEndComponent::Update(float delta_time) {
    return true;
}

bool my::PlayerThrowAttackEndComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerThrowAttackEndComponent::Clone(void) {
    return std::make_shared<my::PlayerThrowAttackEndComponent>(*this);
}

bool my::PlayerThrowAttackEndComponent::Start(void) {
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

bool my::PlayerThrowAttackEndComponent::End(void) {
    /*
    super::End();
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    */
    return true;
}