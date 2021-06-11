#include "PlayerThrowAttackEndComponent.h"

#include "PlayerOmniWrenchComponent.h"


ratchet::PlayerThrowAttackEndComponent::PlayerThrowAttackEndComponent(int priority) :
    super(priority),
    _weapon_com() {
}

ratchet::PlayerThrowAttackEndComponent::PlayerThrowAttackEndComponent(const PlayerThrowAttackEndComponent& obj) :
    super(obj),
    _weapon_com() {
}

ratchet::PlayerThrowAttackEndComponent::~PlayerThrowAttackEndComponent() {
}

std::string ratchet::PlayerThrowAttackEndComponent::GetType(void) const {
    return "PlayerThrowAttackEndComponent";
}

std::string_view ratchet::PlayerThrowAttackEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackEndState;
}

bool ratchet::PlayerThrowAttackEndComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<ratchet::PlayerOmniWrenchComponent>();
    return true;
}

bool ratchet::PlayerThrowAttackEndComponent::Input(void) {
    return false;
}

bool ratchet::PlayerThrowAttackEndComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

bool ratchet::PlayerThrowAttackEndComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerThrowAttackEndComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerThrowAttackEndComponent>(*this);
}

bool ratchet::PlayerThrowAttackEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionThrowAttackEndState);
    return true;
}