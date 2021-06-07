#include "BulletItemMovedComponent.h"

#include "BulletItemComponent.h"


my::BulletItemMovedComponent::BulletItemMovedComponent(int priority) :
    super(priority),
    _speed(),
    _angle(),
    _decrase(0.85f) {
}

my::BulletItemMovedComponent::BulletItemMovedComponent(const BulletItemMovedComponent& obj) :
    super(obj),
    _speed(),
    _angle(),
    _decrase(obj._decrase) {
}

my::BulletItemMovedComponent::~BulletItemMovedComponent() {
}

std::string my::BulletItemMovedComponent::GetType(void) const {
    return "BulletItemMovedComponent";
}

std::string_view my::BulletItemMovedComponent::GetStateType(void) const {
    return state::BulletItemActionType::kMoved;
}

bool my::BulletItemMovedComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::BulletItemMovedComponent::Update(float delta_time) {

    auto velocity_com = super::GetVelocityComponent();
    velocity_com->AddVelocityForce(_speed);
    velocity_com->AddAngularVelocityForce(_angle);

    _speed *= _decrase;
    _angle *= _decrase;
    if (_speed.Length() < 0.2f || _angle.Length() < 0.2) {
        super::ChangeAction(state::BulletItemActionType::kDefault);
    } // if
    return true;
}

bool my::BulletItemMovedComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::BulletItemMovedComponent::Clone(void) {
    return std::make_shared<my::BulletItemMovedComponent>(*this);
}

bool my::BulletItemMovedComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();

    auto type_com = super::GetOwner()->GetComponent<my::BulletItemComponent>();
    auto param = type_com->GetActorParam();
    _speed = param.speed;
    _angle = param.angle;
    return true;
}

bool my::BulletItemMovedComponent::End(void) {
    super::End();
    return true;
}