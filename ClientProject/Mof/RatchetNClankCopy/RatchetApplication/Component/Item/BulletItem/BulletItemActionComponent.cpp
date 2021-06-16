#include "BulletItemActionComponent.h"


std::shared_ptr<ratchet::component::VelocityComponent> ratchet::component::item::bulletitem::BulletItemActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool ratchet::component::item::bulletitem::BulletItemActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

ratchet::component::item::bulletitem::BulletItemActionComponent::BulletItemActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com() {
}

ratchet::component::item::bulletitem::BulletItemActionComponent::BulletItemActionComponent(const BulletItemActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com() {
}

ratchet::component::item::bulletitem::BulletItemActionComponent::~BulletItemActionComponent() {
}

std::string ratchet::component::item::bulletitem::BulletItemActionComponent::GetType(void) const {
    return "BulletItemActionComponent";
}

bool ratchet::component::item::bulletitem::BulletItemActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<ratchet::component::item::bulletitem::BulletItemActionStateComponent>();
    return true;
}

bool ratchet::component::item::bulletitem::BulletItemActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    return true;
}