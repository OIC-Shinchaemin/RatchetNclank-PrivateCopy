#include "BoltActionComponent.h"


std::shared_ptr<my::VelocityComponent> my::BoltActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool my::BoltActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

my::BoltActionComponent::BoltActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com() {
}

my::BoltActionComponent::BoltActionComponent(const BoltActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com() {
}

my::BoltActionComponent::~BoltActionComponent() {
}

std::string my::BoltActionComponent::GetType(void) const {
    return "BoltActionComponent";
}

bool my::BoltActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::BoltActionStateComponent>();
    return true;
}

bool my::BoltActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    return true;
}