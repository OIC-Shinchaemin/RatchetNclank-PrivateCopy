#include "NanotechItemActionComponent.h"


std::shared_ptr<ratchet::component::VelocityComponent> ratchet::component::item::nanotechitem::NanotechItemActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool ratchet::component::item::nanotechitem::NanotechItemActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

ratchet::component::item::nanotechitem::NanotechItemActionComponent::NanotechItemActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com() {
}

ratchet::component::item::nanotechitem::NanotechItemActionComponent::NanotechItemActionComponent(const NanotechItemActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com() {
}

ratchet::component::item::nanotechitem::NanotechItemActionComponent::~NanotechItemActionComponent() {
}

std::string ratchet::component::item::nanotechitem::NanotechItemActionComponent::GetType(void) const {
    return "NanotechItemActionComponent";
}

bool ratchet::component::item::nanotechitem::NanotechItemActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<ratchet::component::item::nanotechitem::NanotechItemActionStateComponent>();
    return true;
}

bool ratchet::component::item::nanotechitem::NanotechItemActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    return true;
}