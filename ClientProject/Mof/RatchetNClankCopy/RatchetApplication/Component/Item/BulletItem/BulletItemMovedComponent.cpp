#include "BulletItemMovedComponent.h"

#include "BulletItemComponent.h"


ratchet::component::item::bulletitem::BulletItemMovedComponent::BulletItemMovedComponent(int priority) :
    super(priority),
    _speed(),
    _angle(),
    _decrase(0.85f) {
}

ratchet::component::item::bulletitem::BulletItemMovedComponent::BulletItemMovedComponent(const BulletItemMovedComponent& obj) :
    super(obj),
    _speed(),
    _angle(),
    _decrase(obj._decrase) {
}

ratchet::component::item::bulletitem::BulletItemMovedComponent::~BulletItemMovedComponent() {
}

std::string ratchet::component::item::bulletitem::BulletItemMovedComponent::GetType(void) const {
    return "BulletItemMovedComponent";
}

std::string_view ratchet::component::item::bulletitem::BulletItemMovedComponent::GetStateType(void) const {
    return state::BulletItemActionType::kMoved;
}

bool ratchet::component::item::bulletitem::BulletItemMovedComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::component::item::bulletitem::BulletItemMovedComponent::Update(float delta_time) {

    auto velocity_com = super::GetVelocityComponent();
    velocity_com->AddVelocityForce(_speed);
    //velocity_com->AddAngularVelocityForce(_angle);

    _speed *= _decrase;
    _angle *= _decrase;
    if (_speed.Length() < 0.2f || _angle.Length() < 0.2) {
        super::ChangeAction(state::BulletItemActionType::kDefault);
    } // if
    return true;
}

bool ratchet::component::item::bulletitem::BulletItemMovedComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::item::bulletitem::BulletItemMovedComponent::Clone(void) {
    return std::make_shared<ratchet::component::item::bulletitem::BulletItemMovedComponent>(*this);
}

bool ratchet::component::item::bulletitem::BulletItemMovedComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();

    auto type_com = super::GetOwner()->GetComponent<ratchet::component::item::bulletitem::BulletItemComponent>();
    auto param = type_com->GetActorParam();
    _speed = param.speed;
    _angle = param.angle;
    return true;
}

bool ratchet::component::item::bulletitem::BulletItemMovedComponent::End(void) {
    super::End();
    return true;
}