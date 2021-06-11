#include "PlayerThrowAttackComponent.h"

#include "PlayerOmniWrenchComponent.h"


rachet::PlayerThrowAttackComponent::PlayerThrowAttackComponent(int priority) :
    super(priority),
    _weapon_com() {
}

rachet::PlayerThrowAttackComponent::PlayerThrowAttackComponent(const PlayerThrowAttackComponent& obj) :
    super(obj),
    _weapon_com() {
}

rachet::PlayerThrowAttackComponent::~PlayerThrowAttackComponent() {
}

std::string rachet::PlayerThrowAttackComponent::GetType(void) const {
    return "PlayerThrowAttackComponent";
}

std::string_view rachet::PlayerThrowAttackComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackState;
}

bool rachet::PlayerThrowAttackComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<rachet::PlayerOmniWrenchComponent>();
    return true;
}

bool rachet::PlayerThrowAttackComponent::Input(void) {
    return false;
}

bool rachet::PlayerThrowAttackComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionThrowAttackEndState);
    } // if
    return true;
}

bool rachet::PlayerThrowAttackComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerThrowAttackComponent::Clone(void) {
    return std::make_shared<rachet::PlayerThrowAttackComponent>(*this);
}

bool rachet::PlayerThrowAttackComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionThrowAttackState);

    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Activate();
    } // if
    return true;
}

bool rachet::PlayerThrowAttackComponent::End(void) {
    super::End();
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    return true;
}