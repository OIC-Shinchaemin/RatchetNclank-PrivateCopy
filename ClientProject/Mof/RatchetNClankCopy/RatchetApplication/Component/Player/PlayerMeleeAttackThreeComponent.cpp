#include "PlayerMeleeAttackThreeComponent.h"

#include "PlayerMoveComponent.h"
#include "PlayerOmniWrenchComponent.h"


ratchet::PlayerMeleeAttackThreeComponent::PlayerMeleeAttackThreeComponent(int priority) :
    super(priority),
    _move_com(),
    _weapon_com() {
}

ratchet::PlayerMeleeAttackThreeComponent::PlayerMeleeAttackThreeComponent(const PlayerMeleeAttackThreeComponent& obj) :
    super(obj),
    _move_com(),
    _weapon_com() {
}

ratchet::PlayerMeleeAttackThreeComponent::~PlayerMeleeAttackThreeComponent() {
}

std::string ratchet::PlayerMeleeAttackThreeComponent::GetType(void) const {
    return "PlayerMeleeAttackThreeComponent";
}

std::string_view ratchet::PlayerMeleeAttackThreeComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackThreeState;
}

bool ratchet::PlayerMeleeAttackThreeComponent::Initialize(void) {
    super::Initialize();

    _move_com = super::GetOwner()->GetComponent<ratchet::ActionComponent>()->GetComponent<ratchet::PlayerMoveComponent>();
    _weapon_com = super::GetOwner()->GetComponent<ratchet::PlayerOmniWrenchComponent>();
    return true;
}

bool ratchet::PlayerMeleeAttackThreeComponent::Input(void) {
    return false;
}

bool ratchet::PlayerMeleeAttackThreeComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMeleeAttackThreeEndState);
    } // if
    return true;
}

bool ratchet::PlayerMeleeAttackThreeComponent::Release(void) {
    super::Release();
    _move_com.reset();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerMeleeAttackThreeComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerMeleeAttackThreeComponent>(*this);
}

bool ratchet::PlayerMeleeAttackThreeComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackThreeState);

    if (auto move_com = _move_com.lock()) {
        Mof::CVector2 in; float move_angle;
        float move_speed = 20.0f; float angular_speed = 0.0f; float ideal_angle = super::GetOwner()->GetRotate().y;
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

bool ratchet::PlayerMeleeAttackThreeComponent::End(void) {
    super::End();
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    return true;
}