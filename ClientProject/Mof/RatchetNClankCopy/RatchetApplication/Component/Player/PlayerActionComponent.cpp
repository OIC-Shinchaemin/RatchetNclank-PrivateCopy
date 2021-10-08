#include "PlayerActionComponent.h"


std::shared_ptr<ratchet::component::TransformComponent> ratchet::component::player::action::PlayerActionComponent::GetTransformComponent(void) const {
    if (auto com = _transform_com.lock()) {
        return com;
    } // if
    return nullptr;
}

std::shared_ptr<ratchet::component::VelocityComponent> ratchet::component::player::action::PlayerActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

std::shared_ptr<ratchet::component::CameraComponent> ratchet::component::player::action::PlayerActionComponent::GetCameraComponent(void) const {
    if (auto com = _camera_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool ::ratchet::component::player::action::PlayerActionComponent::IsEndMotion(void) const {
    _ASSERT_EXPR(!_motion_com.expired(), L"無効なポインタを保持しています");
    auto motion_com = _motion_com.lock();
    return motion_com->IsEndMotion();
}

bool ::ratchet::component::player::action::PlayerActionComponent::CanTransitionActionState(const std::string& next) const {
    _ASSERT_EXPR(!_state_com.expired(), L"無効なポインタを保持しています");
    auto state_com = _state_com.lock();
    return state_com->CanTransition(next);
}

bool ::ratchet::component::player::action::PlayerActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

bool ::ratchet::component::player::action::PlayerActionComponent::ChangeMotionState(const std::string& name) {
    if (auto state_com = _motion_state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

::ratchet::component::player::action::PlayerActionComponent::PlayerActionComponent(int priority) :
    super(priority),
    _transform_com(),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com(),
    _camera_com() {
}

::ratchet::component::player::action::PlayerActionComponent::PlayerActionComponent(const PlayerActionComponent& obj) :
    super(obj),
    _transform_com(),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com(),
    _camera_com() {
}

::ratchet::component::player::action::PlayerActionComponent::~PlayerActionComponent() {
}

std::string ratchet::component::player::action::PlayerActionComponent::GetType(void) const {
    return "PlayerActionComponent";
}

bool ::ratchet::component::player::action::PlayerActionComponent::Initialize(void) {
    super::Initialize();
    _transform_com = super::GetOwner()->GetComponent<ratchet::component::TransformComponent>();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<ratchet::component::player::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<ratchet::component::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<ratchet::component::MotionStateComponent>();
    _camera_com = super::GetOwner()->GetComponent<ratchet::component::CameraComponent>();
    return true;
}

bool ::ratchet::component::player::action::PlayerActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    _motion_com.reset();
    _motion_state_com.reset();
    return true;
}