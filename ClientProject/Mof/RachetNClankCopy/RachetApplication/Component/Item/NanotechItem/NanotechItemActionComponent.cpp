#include "NanotechItemActionComponent.h"


std::shared_ptr<my::VelocityComponent> my::NanotechItemActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool my::NanotechItemActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

my::NanotechItemActionComponent::NanotechItemActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com() {
}

my::NanotechItemActionComponent::NanotechItemActionComponent(const NanotechItemActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com() {
}

my::NanotechItemActionComponent::~NanotechItemActionComponent() {
}

std::string my::NanotechItemActionComponent::GetType(void) const {
    return "NanotechItemActionComponent";
}

bool my::NanotechItemActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::NanotechItemActionStateComponent>();
    return true;
}

bool my::NanotechItemActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    return true;
}