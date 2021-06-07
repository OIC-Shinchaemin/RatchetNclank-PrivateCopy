#include "BulletItemActionComponent.h"


std::shared_ptr<my::VelocityComponent> my::BulletItemActionComponent::GetVelocityComponent(void) const {
    if (auto com = _velocity_com.lock()) {
        return com;
    } // if
    return nullptr;
}

bool my::BulletItemActionComponent::ChangeActionState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
        return true;
    } // if
    return false;
}

my::BulletItemActionComponent::BulletItemActionComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com() {
}

my::BulletItemActionComponent::BulletItemActionComponent(const BulletItemActionComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com() {
}

my::BulletItemActionComponent::~BulletItemActionComponent() {
}

std::string my::BulletItemActionComponent::GetType(void) const {
    return "BulletItemActionComponent";
}

bool my::BulletItemActionComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::BulletItemActionStateComponent>();
    return true;
}

bool my::BulletItemActionComponent::Release(void) {
    super::Release();
    _velocity_com.reset();
    _state_com.reset();
    return true;
}