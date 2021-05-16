#include "PlayerMeleeAttackOneComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"
#include "PlayerMoveComponent.h"
#include "PlayerWeaponComponent.h"


void my::PlayerMeleeAttackOneComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::PlayerMeleeAttackOneComponent::PlayerMeleeAttackOneComponent(int priority) :
    super(priority),
    _next_reserve(false),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com(),
    _move_com(),
    _weapon_com() {
}

my::PlayerMeleeAttackOneComponent::PlayerMeleeAttackOneComponent(const PlayerMeleeAttackOneComponent& obj) :
    super(obj),
    _next_reserve(false),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com(),
    _move_com(),
    _weapon_com() {
}

my::PlayerMeleeAttackOneComponent::~PlayerMeleeAttackOneComponent() {
}

std::string my::PlayerMeleeAttackOneComponent::GetType(void) const {
    return "PlayerMeleeAttackOneComponent";
}

std::string_view my::PlayerMeleeAttackOneComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackOneState;
}

bool my::PlayerMeleeAttackOneComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    _move_com = super::GetOwner()->GetComponent<my::PlayerMoveComponent>();
    _weapon_com = super::GetOwner()->GetComponent<my::PlayerWeaponComponent>();
    return true;
}

bool my::PlayerMeleeAttackOneComponent::Update(float delta_time) {
    auto state_com = _state_com.lock();
    auto motion_com = _motion_com.lock();
    auto motion_state_com = _motion_state_com.lock();


    if (::g_pInput->IsKeyPush(MOFKEY_Z) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        _next_reserve = true;
    } // if

    if (motion_com->IsEndMotion()) {
        if (_next_reserve) {
            state_com->ChangeState(state::PlayerActionStateType::kPlayerActionMeleeAttackTwoState);
        } // if
        else {
            state_com->ChangeState(state::PlayerActionStateType::kPlayerActionMeleeAttackOneEndState);
        } // else
    } // if
    return true;
}

bool my::PlayerMeleeAttackOneComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerMeleeAttackOneComponent::Clone(void) {
    return std::make_shared<my::PlayerMeleeAttackOneComponent>(*this);
}

bool my::PlayerMeleeAttackOneComponent::Start(void) {
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
    return true;
}

bool my::PlayerMeleeAttackOneComponent::End(void) {
    super::End();
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    return true;
}