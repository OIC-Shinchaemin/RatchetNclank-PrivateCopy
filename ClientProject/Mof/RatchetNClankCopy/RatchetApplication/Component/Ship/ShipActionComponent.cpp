#include "ShipActionComponent.h"


std::shared_ptr<ratchet::component::VelocityComponent> ratchet::component::ship::ShipActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool ratchet::component::ship::ShipActionComponent::IsEndMotion(void) const {
    _ASSERT_EXPR(!_motion_com.expired(), L"無効なポインタを保持しています");
    auto motion_com = _motion_com.lock();
    return motion_com->IsEndMotion();
}

bool ratchet::component::ship::ShipActionComponent::CanTransitionActionState(const std::string& next) const {
    _ASSERT_EXPR(!_state_com.expired(), L"無効なポインタを保持しています");
    auto state_com = _state_com.lock();
    return state_com->CanTransition(next);
}

bool ratchet::component::ship::ShipActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

bool ratchet::component::ship::ShipActionComponent::ChangeMotionState(const std::string& name) {
    if (auto state_com = _motion_state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

ratchet::component::ship::ShipActionComponent::ShipActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

ratchet::component::ship::ShipActionComponent::ShipActionComponent(const ShipActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

ratchet::component::ship::ShipActionComponent::~ShipActionComponent() {
}

std::string ratchet::component::ship::ShipActionComponent::GetType(void) const {
    return "ShipActionComponent";
}

bool ratchet::component::ship::ShipActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<ratchet::component::ship::ShipStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<ratchet::component::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<ratchet::component::MotionStateComponent>();
    return true;
}

bool ratchet::component::ship::ShipActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    _motion_com.reset();
    _motion_state_com.reset();
    return true;
}