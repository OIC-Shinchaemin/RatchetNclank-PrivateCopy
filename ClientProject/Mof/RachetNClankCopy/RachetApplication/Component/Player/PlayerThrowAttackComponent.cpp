#include "PlayerThrowAttackComponent.h"

#include "PlayerWeaponComponent.h"


my::PlayerThrowAttackComponent::PlayerThrowAttackComponent(int priority) :
    super(priority),
    _weapon_com() {
}

my::PlayerThrowAttackComponent::PlayerThrowAttackComponent(const PlayerThrowAttackComponent& obj) :
    super(obj),
    _weapon_com() {
}

my::PlayerThrowAttackComponent::~PlayerThrowAttackComponent() {
}

std::string my::PlayerThrowAttackComponent::GetType(void) const {
    return "PlayerThrowAttackComponent";
}

std::string_view my::PlayerThrowAttackComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackState;
}

bool my::PlayerThrowAttackComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<my::PlayerWeaponComponent>();
    return true;
}

bool my::PlayerThrowAttackComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionThrowAttackEndState);
    } // if
    return true;
}

bool my::PlayerThrowAttackComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<my::Component> my::PlayerThrowAttackComponent::Clone(void) {
    return std::make_shared<my::PlayerThrowAttackComponent>(*this);
}

bool my::PlayerThrowAttackComponent::Start(void) {
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

bool my::PlayerThrowAttackComponent::End(void) {
    super::End();
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    return true;
}