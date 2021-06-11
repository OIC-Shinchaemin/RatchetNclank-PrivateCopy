#include "BoltMovedComponent.h"

#include "BoltComponent.h"


rachet::BoltMovedComponent::BoltMovedComponent(int priority) :
    super(priority),
    _speed(),
    _angle(),
    _decrase(0.85f) {
}

rachet::BoltMovedComponent::BoltMovedComponent(const BoltMovedComponent& obj) :
    super(obj),
    _speed(),
    _angle(),
    _decrase(obj._decrase) {
}

rachet::BoltMovedComponent::~BoltMovedComponent() {
}

std::string rachet::BoltMovedComponent::GetType(void) const {
    return "BoltMovedComponent";
}

std::string_view rachet::BoltMovedComponent::GetStateType(void) const {
    return state::BoltActionType::kMoved;
}

bool rachet::BoltMovedComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool rachet::BoltMovedComponent::Update(float delta_time) {

    auto velocity_com = super::GetVelocityComponent();
    velocity_com->AddVelocityForce(_speed);
    velocity_com->AddAngularVelocityForce(_angle);

    _speed *= _decrase;
    _angle *= _decrase;
    if (_speed.Length() < 0.2f || _angle.Length() < 0.2) {
        super::ChangeAction(state::BoltActionType::kDefault);
    } // if
    return true;
}

bool rachet::BoltMovedComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::BoltMovedComponent::Clone(void) {
    return std::make_shared<rachet::BoltMovedComponent>(*this);
}

bool rachet::BoltMovedComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();

    auto type_com = super::GetOwner()->GetComponent<rachet::BoltComponent>();
    auto param = type_com->GetActorParam();
    _speed = param.speed;
    _angle = param.angle;
    return true;
}

bool rachet::BoltMovedComponent::End(void) {
    super::End();
    return true;
}