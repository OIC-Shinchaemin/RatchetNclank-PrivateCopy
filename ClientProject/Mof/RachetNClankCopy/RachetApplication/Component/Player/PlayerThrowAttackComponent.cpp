#include "PlayerThrowAttackComponent.h"

#include "PlayerOmniWrenchComponent.h"


ratchet::PlayerThrowAttackComponent::PlayerThrowAttackComponent(int priority) :
    super(priority),
    _weapon_com() {
}

ratchet::PlayerThrowAttackComponent::PlayerThrowAttackComponent(const PlayerThrowAttackComponent& obj) :
    super(obj),
    _weapon_com() {
}

ratchet::PlayerThrowAttackComponent::~PlayerThrowAttackComponent() {
}

std::string ratchet::PlayerThrowAttackComponent::GetType(void) const {
    return "PlayerThrowAttackComponent";
}

std::string_view ratchet::PlayerThrowAttackComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackState;
}

bool ratchet::PlayerThrowAttackComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<ratchet::PlayerOmniWrenchComponent>();
    return true;
}

bool ratchet::PlayerThrowAttackComponent::Input(void) {
    return false;
}

bool ratchet::PlayerThrowAttackComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionThrowAttackEndState);
    } // if
    return true;
}

bool ratchet::PlayerThrowAttackComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::PlayerThrowAttackComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerThrowAttackComponent>(*this);
}

bool ratchet::PlayerThrowAttackComponent::Start(void) {
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

bool ratchet::PlayerThrowAttackComponent::End(void) {
    super::End();
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    return true;
}