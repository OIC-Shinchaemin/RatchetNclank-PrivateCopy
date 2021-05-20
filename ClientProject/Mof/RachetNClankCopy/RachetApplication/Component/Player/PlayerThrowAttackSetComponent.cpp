#include "PlayerThrowAttackSetComponent.h"

#include "PlayerWeaponComponent.h"


my::PlayerThrowAttackSetComponent::PlayerThrowAttackSetComponent(int priority) :
    super(priority),
    _weapon_com() {
}

my::PlayerThrowAttackSetComponent::PlayerThrowAttackSetComponent(const PlayerThrowAttackSetComponent& obj) :
    super(obj),
    _weapon_com() {
}

my::PlayerThrowAttackSetComponent::~PlayerThrowAttackSetComponent() {
}

std::string my::PlayerThrowAttackSetComponent::GetType(void) const {
    return "PlayerThrowAttackSetComponent";
}

std::string_view my::PlayerThrowAttackSetComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackSetState;
}

bool my::PlayerThrowAttackSetComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<my::PlayerWeaponComponent>();
    return true;
}

bool my::PlayerThrowAttackSetComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionThrowAttackState);
    } // if
    return true;
}

bool my::PlayerThrowAttackSetComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<my::Component> my::PlayerThrowAttackSetComponent::Clone(void) {
    return std::make_shared<my::PlayerThrowAttackSetComponent>(*this);
}

bool my::PlayerThrowAttackSetComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionThrowAttackSetState);
    //if (auto motion_state_com = _motion_state_com.lock()) {
        //motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionThrowAttackSetState);
    //} // if
    /*
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Activate();
    } // if
    */
    return true;
}