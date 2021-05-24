#include "PlayerThrowAttackEndComponent.h"

#include "PlayerOmniWrenchComponent.h"


my::PlayerThrowAttackEndComponent::PlayerThrowAttackEndComponent(int priority) :
    super(priority),
    _weapon_com() {
}

my::PlayerThrowAttackEndComponent::PlayerThrowAttackEndComponent(const PlayerThrowAttackEndComponent& obj) :
    super(obj),
    _weapon_com() {
}

my::PlayerThrowAttackEndComponent::~PlayerThrowAttackEndComponent() {
}

std::string my::PlayerThrowAttackEndComponent::GetType(void) const {
    return "PlayerThrowAttackEndComponent";
}

std::string_view my::PlayerThrowAttackEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackEndState;
}

bool my::PlayerThrowAttackEndComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<my::PlayerOmniWrenchComponent>();
    return true;
}

bool my::PlayerThrowAttackEndComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

bool my::PlayerThrowAttackEndComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<my::Component> my::PlayerThrowAttackEndComponent::Clone(void) {
    return std::make_shared<my::PlayerThrowAttackEndComponent>(*this);
}

bool my::PlayerThrowAttackEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionThrowAttackEndState);
    return true;
}