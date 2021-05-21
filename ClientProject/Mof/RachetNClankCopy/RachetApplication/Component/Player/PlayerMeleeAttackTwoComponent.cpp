#include "PlayerMeleeAttackTwoComponent.h"

#include "PlayerMoveComponent.h"
#include "PlayerWeaponComponent.h"


my::PlayerMeleeAttackTwoComponent::PlayerMeleeAttackTwoComponent(int priority) :
    super(priority),
    _next_reserve(false),
    _move_com(),
    _weapon_com() {
}

my::PlayerMeleeAttackTwoComponent::PlayerMeleeAttackTwoComponent(const PlayerMeleeAttackTwoComponent& obj) :
    super(obj),
    _next_reserve(false),
    _move_com(),
    _weapon_com() {
}

my::PlayerMeleeAttackTwoComponent::~PlayerMeleeAttackTwoComponent() {
}

std::string my::PlayerMeleeAttackTwoComponent::GetType(void) const {
    return "PlayerMeleeAttackTwoComponent";
}

std::string_view my::PlayerMeleeAttackTwoComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackTwoState;
}

bool my::PlayerMeleeAttackTwoComponent::Initialize(void) {
    super::Initialize();

    _move_com = super::GetOwner()->GetComponent<my::PlayerMoveComponent>();
    _weapon_com = super::GetOwner()->GetComponent<my::PlayerWeaponComponent>();
    return true;
}

bool my::PlayerMeleeAttackTwoComponent::Update(float delta_time) {
    if (::g_pInput->IsKeyPush(MOFKEY_Z) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        _next_reserve = true;
    } // if

    if (super::IsEndMotion()) {
        if (_next_reserve) {
            super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMeleeAttackThreeState);
        } // if
        else {
            super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMeleeAttackTwoEndState);
        } // else
    } // if
    return true;
}

bool my::PlayerMeleeAttackTwoComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerMeleeAttackTwoComponent::Clone(void) {
    return std::make_shared<my::PlayerMeleeAttackTwoComponent>(*this);
}

bool my::PlayerMeleeAttackTwoComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackTwoState);
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
    return true;
}

bool my::PlayerMeleeAttackTwoComponent::End(void) {
    super::End();
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    return true;
}