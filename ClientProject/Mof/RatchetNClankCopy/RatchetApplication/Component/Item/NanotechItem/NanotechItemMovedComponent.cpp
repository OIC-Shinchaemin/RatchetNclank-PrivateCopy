#include "NanotechItemMovedComponent.h"

#include "NanotechItemComponent.h"


ratchet::component::item::nanotechitem::NanotechItemMovedComponent::NanotechItemMovedComponent(int priority) :
    super(priority),
    _speed(),
    _angle(),
    _decrase(0.85f) {
}

ratchet::component::item::nanotechitem::NanotechItemMovedComponent::NanotechItemMovedComponent(const NanotechItemMovedComponent& obj) :
    super(obj),
    _speed(),
    _angle(),
    _decrase(obj._decrase) {
}

ratchet::component::item::nanotechitem::NanotechItemMovedComponent::~NanotechItemMovedComponent() {
}

std::string ratchet::component::item::nanotechitem::NanotechItemMovedComponent::GetType(void) const {
    return "NanotechItemMovedComponent";
}

std::string_view ratchet::component::item::nanotechitem::NanotechItemMovedComponent::GetStateType(void) const {
    return state::NanotechItemActionType::kMoved;
}

bool ratchet::component::item::nanotechitem::NanotechItemMovedComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool ratchet::component::item::nanotechitem::NanotechItemMovedComponent::Update(float delta_time) {

    auto velocity_com = super::GetVelocityComponent();
    velocity_com->AddVelocityForce(_speed);
    //velocity_com->AddAngularVelocityForce(_angle);

    _speed *= _decrase;
    _angle *= _decrase;
    if (_speed.Length() < 0.2f || _angle.Length() < 0.2) {
        super::ChangeAction(state::NanotechItemActionType::kDefault);
    } // if
    return true;
}

bool ratchet::component::item::nanotechitem::NanotechItemMovedComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::item::nanotechitem::NanotechItemMovedComponent::Clone(void) {
    return std::make_shared<ratchet::component::item::nanotechitem::NanotechItemMovedComponent>(*this);
}

bool ratchet::component::item::nanotechitem::NanotechItemMovedComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();

    auto type_com = super::GetOwner()->GetComponent<ratchet::component::item::nanotechitem::NanotechItemComponent>();
    auto param = type_com->GetActorParam();
    _speed = param.speed;
    _angle = param.angle;
    return true;
}

bool ratchet::component::item::nanotechitem::NanotechItemMovedComponent::End(void) {
    super::End();
    return true;
}