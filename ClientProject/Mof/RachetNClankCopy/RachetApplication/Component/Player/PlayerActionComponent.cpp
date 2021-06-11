#include "PlayerActionComponent.h"


std::shared_ptr<ratchet::VelocityComponent> ratchet::PlayerActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool ratchet::PlayerActionComponent::IsEndMotion(void) const {
    _ASSERT_EXPR(!_motion_com.expired(), L"無効なポインタを保持しています");
    auto motion_com = _motion_com.lock();
    return motion_com->IsEndMotion();
}

bool ratchet::PlayerActionComponent::CanTransitionActionState(const std::string& next) const {
    _ASSERT_EXPR(!_state_com.expired(), L"無効なポインタを保持しています");
    auto state_com = _state_com.lock();
    return state_com->CanTransition(next);
}

bool ratchet::PlayerActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

bool ratchet::PlayerActionComponent::ChangeMotionState(const std::string& name) {
    if (auto state_com = _motion_state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

ratchet::PlayerActionComponent::PlayerActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

ratchet::PlayerActionComponent::PlayerActionComponent(const PlayerActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

ratchet::PlayerActionComponent::~PlayerActionComponent() {
}

std::string ratchet::PlayerActionComponent::GetType(void) const {
    return "PlayerActionComponent";
}

bool ratchet::PlayerActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<ratchet::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<ratchet::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<ratchet::MotionStateComponent>();
    return true;
}

bool ratchet::PlayerActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    _motion_com.reset();
    _motion_state_com.reset();
    return true;
}