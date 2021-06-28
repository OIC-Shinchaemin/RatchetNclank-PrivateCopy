#include "PlayerThrowAttackComponent.h"

#include "PlayerOmniWrenchComponent.h"


ratchet::component::player::action::PlayerThrowAttackComponent::PlayerThrowAttackComponent(int priority) :
    super(priority),
    _weapon_com() {
}

ratchet::component::player::action::PlayerThrowAttackComponent::PlayerThrowAttackComponent(const PlayerThrowAttackComponent& obj) :
    super(obj),
    _weapon_com() {
}

ratchet::component::player::action::PlayerThrowAttackComponent::~PlayerThrowAttackComponent() {
}

std::string ratchet::component::player::action::PlayerThrowAttackComponent::GetType(void) const {
    return "PlayerThrowAttackComponent";
}

std::string_view ratchet::component::player::action::PlayerThrowAttackComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackState;
}

bool ratchet::component::player::action::PlayerThrowAttackComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<ratchet::component::player::PlayerOmniWrenchComponent>();
    return true;
}

bool ratchet::component::player::action::PlayerThrowAttackComponent::Input(void) {
    return false;
}

bool ratchet::component::player::action::PlayerThrowAttackComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionThrowAttackEndState);
    } // if
    return true;
}

bool ratchet::component::player::action::PlayerThrowAttackComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerThrowAttackComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerThrowAttackComponent>(*this);
}

bool ratchet::component::player::action::PlayerThrowAttackComponent::Start(void) {
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

bool ratchet::component::player::action::PlayerThrowAttackComponent::End(void) {
    super::End();
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    return true;
}