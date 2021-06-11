#include "NanotechItemMovedComponent.h"

#include "NanotechItemComponent.h"


rachet::NanotechItemMovedComponent::NanotechItemMovedComponent(int priority) :
    super(priority),
    _speed(),
    _angle(),
    _decrase(0.85f) {
}

rachet::NanotechItemMovedComponent::NanotechItemMovedComponent(const NanotechItemMovedComponent& obj) :
    super(obj),
    _speed(),
    _angle(),
    _decrase(obj._decrase) {
}

rachet::NanotechItemMovedComponent::~NanotechItemMovedComponent() {
}

std::string rachet::NanotechItemMovedComponent::GetType(void) const {
    return "NanotechItemMovedComponent";
}

std::string_view rachet::NanotechItemMovedComponent::GetStateType(void) const {
    return state::NanotechItemActionType::kMoved;
}

bool rachet::NanotechItemMovedComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool rachet::NanotechItemMovedComponent::Update(float delta_time) {

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

bool rachet::NanotechItemMovedComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::NanotechItemMovedComponent::Clone(void) {
    return std::make_shared<rachet::NanotechItemMovedComponent>(*this);
}

bool rachet::NanotechItemMovedComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();

    auto type_com = super::GetOwner()->GetComponent<rachet::NanotechItemComponent>();
    auto param = type_com->GetActorParam();
    _speed = param.speed;
    _angle = param.angle;
    return true;
}

bool rachet::NanotechItemMovedComponent::End(void) {
    super::End();
    return true;
}