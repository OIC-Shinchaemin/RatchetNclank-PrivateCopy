#include "BulletItemMovedComponent.h"

#include "BulletItemComponent.h"


ratchet::BulletItemMovedComponent::BulletItemMovedComponent(int priority) :
    super(priority),
    _speed(),
    _angle(),
    _decrase(0.85f) {
}

ratchet::BulletItemMovedComponent::BulletItemMovedComponent(const BulletItemMovedComponent& obj) :
    super(obj),
    _speed(),
    _angle(),
    _decrase(obj._decrase) {
}

ratchet::BulletItemMovedComponent::~BulletItemMovedComponent() {
}

std::string ratchet::BulletItemMovedComponent::GetType(void) const {
    return "BulletItemMovedComponent";
}

std::string_view ratchet::BulletItemMovedComponent::GetStateType(void) const {
    return state::BulletItemActionType::kMoved;
}

bool ratchet::BulletItemMovedComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::BulletItemMovedComponent::Update(float delta_time) {

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

bool ratchet::BulletItemMovedComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::BulletItemMovedComponent::Clone(void) {
    return std::make_shared<ratchet::BulletItemMovedComponent>(*this);
}

bool ratchet::BulletItemMovedComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();

    auto type_com = super::GetOwner()->GetComponent<ratchet::BulletItemComponent>();
    auto param = type_com->GetActorParam();
    _speed = param.speed;
    _angle = param.angle;
    return true;
}

bool ratchet::BulletItemMovedComponent::End(void) {
    super::End();
    return true;
}