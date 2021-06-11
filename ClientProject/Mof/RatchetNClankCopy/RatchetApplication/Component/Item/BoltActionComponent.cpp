#include "BoltActionComponent.h"


std::shared_ptr<ratchet::VelocityComponent> ratchet::BoltActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool ratchet::BoltActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

ratchet::BoltActionComponent::BoltActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com() {
}

ratchet::BoltActionComponent::BoltActionComponent(const BoltActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com() {
}

ratchet::BoltActionComponent::~BoltActionComponent() {
}

std::string ratchet::BoltActionComponent::GetType(void) const {
    return "BoltActionComponent";
}

bool ratchet::BoltActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<ratchet::BoltActionStateComponent>();
    return true;
}

bool ratchet::BoltActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    return true;
}