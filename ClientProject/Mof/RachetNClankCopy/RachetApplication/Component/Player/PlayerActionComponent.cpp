#include "PlayerActionComponent.h"


std::shared_ptr<rachet::VelocityComponent> rachet::PlayerActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool rachet::PlayerActionComponent::IsEndMotion(void) const {
    _ASSERT_EXPR(!_motion_com.expired(), L"無効なポインタを保持しています");
    auto motion_com = _motion_com.lock();
    return motion_com->IsEndMotion();
}

bool rachet::PlayerActionComponent::CanTransitionActionState(const std::string& next) const {
    _ASSERT_EXPR(!_state_com.expired(), L"無効なポインタを保持しています");
    auto state_com = _state_com.lock();
    return state_com->CanTransition(next);
}

bool rachet::PlayerActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

bool rachet::PlayerActionComponent::ChangeMotionState(const std::string& name) {
    if (auto state_com = _motion_state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

rachet::PlayerActionComponent::PlayerActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

rachet::PlayerActionComponent::PlayerActionComponent(const PlayerActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

rachet::PlayerActionComponent::~PlayerActionComponent() {
}

std::string rachet::PlayerActionComponent::GetType(void) const {
    return "PlayerActionComponent";
}

bool rachet::PlayerActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<rachet::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<rachet::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<rachet::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<rachet::MotionStateComponent>();
    return true;
}

bool rachet::PlayerActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    _motion_com.reset();
    _motion_state_com.reset();
    return true;
}