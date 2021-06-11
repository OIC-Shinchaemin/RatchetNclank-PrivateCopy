#include "BoltMovedComponent.h"

#include "BoltComponent.h"


ratchet::BoltMovedComponent::BoltMovedComponent(int priority) :
    super(priority),
    _speed(),
    _angle(),
    _decrase(0.85f) {
}

ratchet::BoltMovedComponent::BoltMovedComponent(const BoltMovedComponent& obj) :
    super(obj),
    _speed(),
    _angle(),
    _decrase(obj._decrase) {
}

ratchet::BoltMovedComponent::~BoltMovedComponent() {
}

std::string ratchet::BoltMovedComponent::GetType(void) const {
    return "BoltMovedComponent";
}

std::string_view ratchet::BoltMovedComponent::GetStateType(void) const {
    return state::BoltActionType::kMoved;
}

bool ratchet::BoltMovedComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::BoltMovedComponent::Update(float delta_time) {

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

bool ratchet::BoltMovedComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::BoltMovedComponent::Clone(void) {
    return std::make_shared<ratchet::BoltMovedComponent>(*this);
}

bool ratchet::BoltMovedComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();

    auto type_com = super::GetOwner()->GetComponent<ratchet::BoltComponent>();
    auto param = type_com->GetActorParam();
    _speed = param.speed;
    _angle = param.angle;
    return true;
}

bool ratchet::BoltMovedComponent::End(void) {
    super::End();
    return true;
}