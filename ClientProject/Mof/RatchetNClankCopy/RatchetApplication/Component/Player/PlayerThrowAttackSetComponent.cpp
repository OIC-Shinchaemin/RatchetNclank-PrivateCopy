#include "PlayerThrowAttackSetComponent.h"

#include "PlayerOmniWrenchComponent.h"


ratchet::PlayerThrowAttackSetComponent::PlayerThrowAttackSetComponent(int priority) :
    super(priority),
    _weapon_com() {
}

ratchet::PlayerThrowAttackSetComponent::PlayerThrowAttackSetComponent(const PlayerThrowAttackSetComponent& obj) :
    super(obj),
    _weapon_com() {
}

ratchet::PlayerThrowAttackSetComponent::~PlayerThrowAttackSetComponent() {
}

std::string ratchet::PlayerThrowAttackSetComponent::GetType(void) const {
    return "PlayerThrowAttackSetComponent";
}

std::string_view ratchet::PlayerThrowAttackSetComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackSetState;
}

bool ratchet::PlayerThrowAttackSetComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<ratchet::PlayerOmniWrenchComponent>();
    return true;
}

bool ratchet::PlayerThrowAttackSetComponent::Input(void) {
    return false;
}

bool ratchet::PlayerThrowAttackSetComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionThrowAttackState);
    } // if
    return true;
}

bool ratchet::PlayerThrowAttackSetComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerThrowAttackSetComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerThrowAttackSetComponent>(*this);
}

bool ratchet::PlayerThrowAttackSetComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionThrowAttackSetState);
    return true;
}