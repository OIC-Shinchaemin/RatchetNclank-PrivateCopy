#include "NanotechItemMovedComponent.h"

#include "NanotechItemComponent.h"


my::NanotechItemMovedComponent::NanotechItemMovedComponent(int priority) :
    super(priority),
    _speed(),
    _angle(),
    _decrase(0.85f) {
}

my::NanotechItemMovedComponent::NanotechItemMovedComponent(const NanotechItemMovedComponent& obj) :
    super(obj),
    _speed(),
    _angle(),
    _decrase(obj._decrase) {
}

my::NanotechItemMovedComponent::~NanotechItemMovedComponent() {
}

std::string my::NanotechItemMovedComponent::GetType(void) const {
    return "NanotechItemMovedComponent";
}

std::string_view my::NanotechItemMovedComponent::GetStateType(void) const {
    return state::NanotechItemActionType::kMoved;
}

bool my::NanotechItemMovedComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::NanotechItemMovedComponent::Update(float delta_time) {

    auto velocity_com = super::GetVelocityComponent();
    velocity_com->AddVelocityForce(_speed);
    velocity_com->AddAngularVelocityForce(_angle);

    _speed *= _decrase;
    _angle *= _decrase;
    if (_speed.Length() < 0.2f || _angle.Length() < 0.2) {
        super::ChangeAction(state::NanotechItemActionType::kDefault);
    } // if
    return true;
}

bool my::NanotechItemMovedComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::NanotechItemMovedComponent::Clone(void) {
    return std::make_shared<my::NanotechItemMovedComponent>(*this);
}

bool my::NanotechItemMovedComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();

    auto type_com = super::GetOwner()->GetComponent<my::NanotechItemComponent>();
    auto param = type_com->GetActorParam();
    _speed = param.speed;
    _angle = param.angle;
    return true;
}

bool my::NanotechItemMovedComponent::End(void) {
    super::End();
    return true;
}