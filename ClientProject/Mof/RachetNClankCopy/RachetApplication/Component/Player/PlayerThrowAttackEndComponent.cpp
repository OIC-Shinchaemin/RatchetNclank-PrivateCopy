#include "PlayerThrowAttackEndComponent.h"

#include "PlayerOmniWrenchComponent.h"


rachet::PlayerThrowAttackEndComponent::PlayerThrowAttackEndComponent(int priority) :
    super(priority),
    _weapon_com() {
}

rachet::PlayerThrowAttackEndComponent::PlayerThrowAttackEndComponent(const PlayerThrowAttackEndComponent& obj) :
    super(obj),
    _weapon_com() {
}

rachet::PlayerThrowAttackEndComponent::~PlayerThrowAttackEndComponent() {
}

std::string rachet::PlayerThrowAttackEndComponent::GetType(void) const {
    return "PlayerThrowAttackEndComponent";
}

std::string_view rachet::PlayerThrowAttackEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackEndState;
}

bool rachet::PlayerThrowAttackEndComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<rachet::PlayerOmniWrenchComponent>();
    return true;
}

bool rachet::PlayerThrowAttackEndComponent::Input(void) {
    return false;
}

bool rachet::PlayerThrowAttackEndComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

bool rachet::PlayerThrowAttackEndComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerThrowAttackEndComponent::Clone(void) {
    return std::make_shared<rachet::PlayerThrowAttackEndComponent>(*this);
}

bool rachet::PlayerThrowAttackEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionThrowAttackEndState);
    return true;
}