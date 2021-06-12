#include "BoltActionComponent.h"


std::shared_ptr<ratchet::component::VelocityComponent> ratchet::component::item::BoltActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool ratchet::component::item::BoltActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

ratchet::component::item::BoltActionComponent::BoltActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com() {
}

ratchet::component::item::BoltActionComponent::BoltActionComponent(const BoltActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com() {
}

ratchet::component::item::BoltActionComponent::~BoltActionComponent() {
}

std::string ratchet::component::item::BoltActionComponent::GetType(void) const {
    return "BoltActionComponent";
}

bool ratchet::component::item::BoltActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<ratchet::component::item::BoltActionStateComponent>();
    return true;
}

bool ratchet::component::item::BoltActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    return true;
}