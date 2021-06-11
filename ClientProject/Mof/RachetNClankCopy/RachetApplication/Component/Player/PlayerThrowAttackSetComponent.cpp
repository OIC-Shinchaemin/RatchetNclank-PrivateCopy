#include "PlayerThrowAttackSetComponent.h"

#include "PlayerOmniWrenchComponent.h"


rachet::PlayerThrowAttackSetComponent::PlayerThrowAttackSetComponent(int priority) :
    super(priority),
    _weapon_com() {
}

rachet::PlayerThrowAttackSetComponent::PlayerThrowAttackSetComponent(const PlayerThrowAttackSetComponent& obj) :
    super(obj),
    _weapon_com() {
}

rachet::PlayerThrowAttackSetComponent::~PlayerThrowAttackSetComponent() {
}

std::string rachet::PlayerThrowAttackSetComponent::GetType(void) const {
    return "PlayerThrowAttackSetComponent";
}

std::string_view rachet::PlayerThrowAttackSetComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackSetState;
}

bool rachet::PlayerThrowAttackSetComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<rachet::PlayerOmniWrenchComponent>();
    return true;
}

bool rachet::PlayerThrowAttackSetComponent::Input(void) {
    return false;
}

bool rachet::PlayerThrowAttackSetComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionThrowAttackState);
    } // if
    return true;
}

bool rachet::PlayerThrowAttackSetComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerThrowAttackSetComponent::Clone(void) {
    return std::make_shared<rachet::PlayerThrowAttackSetComponent>(*this);
}

bool rachet::PlayerThrowAttackSetComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionThrowAttackSetState);
    return true;
}