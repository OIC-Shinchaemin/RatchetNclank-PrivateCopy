#include "NanotechItemActionComponent.h"


std::shared_ptr<ratchet::VelocityComponent> ratchet::NanotechItemActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool ratchet::NanotechItemActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

ratchet::NanotechItemActionComponent::NanotechItemActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com() {
}

ratchet::NanotechItemActionComponent::NanotechItemActionComponent(const NanotechItemActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com() {
}

ratchet::NanotechItemActionComponent::~NanotechItemActionComponent() {
}

std::string ratchet::NanotechItemActionComponent::GetType(void) const {
    return "NanotechItemActionComponent";
}

bool ratchet::NanotechItemActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<ratchet::NanotechItemActionStateComponent>();
    return true;
}

bool ratchet::NanotechItemActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    return true;
}