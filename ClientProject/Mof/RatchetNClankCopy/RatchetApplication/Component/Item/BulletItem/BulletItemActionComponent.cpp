#include "BulletItemActionComponent.h"


std::shared_ptr<ratchet::VelocityComponent> ratchet::BulletItemActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool ratchet::BulletItemActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

ratchet::BulletItemActionComponent::BulletItemActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com() {
}

ratchet::BulletItemActionComponent::BulletItemActionComponent(const BulletItemActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com() {
}

ratchet::BulletItemActionComponent::~BulletItemActionComponent() {
}

std::string ratchet::BulletItemActionComponent::GetType(void) const {
    return "BulletItemActionComponent";
}

bool ratchet::BulletItemActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<ratchet::BulletItemActionStateComponent>();
    return true;
}

bool ratchet::BulletItemActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    return true;
}