#include "BoltActionComponent.h"


std::shared_ptr<rachet::VelocityComponent> rachet::BoltActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool rachet::BoltActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

rachet::BoltActionComponent::BoltActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com() {
}

rachet::BoltActionComponent::BoltActionComponent(const BoltActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com() {
}

rachet::BoltActionComponent::~BoltActionComponent() {
}

std::string rachet::BoltActionComponent::GetType(void) const {
    return "BoltActionComponent";
}

bool rachet::BoltActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<rachet::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<rachet::BoltActionStateComponent>();
    return true;
}

bool rachet::BoltActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    return true;
}