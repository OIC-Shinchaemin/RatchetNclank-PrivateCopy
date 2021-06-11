#include "ShipActionComponent.h"


std::shared_ptr<ratchet::VelocityComponent> ratchet::ShipActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool ratchet::ShipActionComponent::IsEndMotion(void) const {
    _ASSERT_EXPR(!_motion_com.expired(), L"無効なポインタを保持しています");
    auto motion_com = _motion_com.lock();
    return motion_com->IsEndMotion();
}

bool ratchet::ShipActionComponent::CanTransitionActionState(const std::string& next) const {
    _ASSERT_EXPR(!_state_com.expired(), L"無効なポインタを保持しています");
    auto state_com = _state_com.lock();
    return state_com->CanTransition(next);
}

bool ratchet::ShipActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

bool ratchet::ShipActionComponent::ChangeMotionState(const std::string& name) {
    if (auto state_com = _motion_state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

ratchet::ShipActionComponent::ShipActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

ratchet::ShipActionComponent::ShipActionComponent(const ShipActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

ratchet::ShipActionComponent::~ShipActionComponent() {
}

std::string ratchet::ShipActionComponent::GetType(void) const {
    return "ShipActionComponent";
}

bool ratchet::ShipActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<ratchet::ShipStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<ratchet::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<ratchet::MotionStateComponent>();
    return true;
}

bool ratchet::ShipActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    _motion_com.reset();
    _motion_state_com.reset();
    return true;
}