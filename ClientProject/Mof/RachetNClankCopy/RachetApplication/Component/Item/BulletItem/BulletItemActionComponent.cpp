#include "BulletItemActionComponent.h"


std::shared_ptr<rachet::VelocityComponent> rachet::BulletItemActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool rachet::BulletItemActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

rachet::BulletItemActionComponent::BulletItemActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com() {
}

rachet::BulletItemActionComponent::BulletItemActionComponent(const BulletItemActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com() {
}

rachet::BulletItemActionComponent::~BulletItemActionComponent() {
}

std::string rachet::BulletItemActionComponent::GetType(void) const {
    return "BulletItemActionComponent";
}

bool rachet::BulletItemActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<rachet::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<rachet::BulletItemActionStateComponent>();
    return true;
}

bool rachet::BulletItemActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    return true;
}