#include "PlayerActionComponent.h"


std::shared_ptr<my::VelocityComponent> my::PlayerActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool my::PlayerActionComponent::IsEndMotion(void) const {
    _ASSERT_EXPR(!_motion_com.expired(), L"無効なポインタを保持しています");
    auto motion_com = _motion_com.lock();
    return motion_com->IsEndMotion();
}

bool my::PlayerActionComponent::CanTransitionActionState(const std::string& next) const {
    _ASSERT_EXPR(!_state_com.expired(), L"無効なポインタを保持しています");
    auto state_com = _state_com.lock();
    return state_com->CanTransition(next);
}

bool my::PlayerActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

bool my::PlayerActionComponent::ChangeMotionState(const std::string& name) {
    if (auto state_com = _motion_state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

my::PlayerActionComponent::PlayerActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerActionComponent::PlayerActionComponent(const PlayerActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerActionComponent::~PlayerActionComponent() {
}

std::string my::PlayerActionComponent::GetType(void) const {
    return "PlayerActionComponent";
}

bool my::PlayerActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::PlayerActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    _motion_com.reset();
    _motion_state_com.reset();
    return true;
}