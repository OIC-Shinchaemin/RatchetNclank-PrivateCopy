#include "NanotechItemActionComponent.h"


std::shared_ptr<rachet::VelocityComponent> rachet::NanotechItemActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool rachet::NanotechItemActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

rachet::NanotechItemActionComponent::NanotechItemActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com() {
}

rachet::NanotechItemActionComponent::NanotechItemActionComponent(const NanotechItemActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com() {
}

rachet::NanotechItemActionComponent::~NanotechItemActionComponent() {
}

std::string rachet::NanotechItemActionComponent::GetType(void) const {
    return "NanotechItemActionComponent";
}

bool rachet::NanotechItemActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<rachet::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<rachet::NanotechItemActionStateComponent>();
    return true;
}

bool rachet::NanotechItemActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    return true;
}