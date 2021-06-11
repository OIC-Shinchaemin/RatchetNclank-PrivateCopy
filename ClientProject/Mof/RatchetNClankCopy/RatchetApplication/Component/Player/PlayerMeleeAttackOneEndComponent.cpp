#include "PlayerMeleeAttackOneEndComponent.h"


ratchet::PlayerMeleeAttackOneEndComponent::PlayerMeleeAttackOneEndComponent(int priority) :
    super(priority) {
}

ratchet::PlayerMeleeAttackOneEndComponent::PlayerMeleeAttackOneEndComponent(const PlayerMeleeAttackOneEndComponent& obj) :
    super(obj) {
}

ratchet::PlayerMeleeAttackOneEndComponent::~PlayerMeleeAttackOneEndComponent() {
}

std::string ratchet::PlayerMeleeAttackOneEndComponent::GetType(void) const {
    return "PlayerMeleeAttackOneEndComponent";
}

std::string_view ratchet::PlayerMeleeAttackOneEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackOneEndState;
}

bool ratchet::PlayerMeleeAttackOneEndComponent::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_N) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMeleeAttackTwoState);
    } // if
    return true;
}

bool ratchet::PlayerMeleeAttackOneEndComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerMeleeAttackOneEndComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerMeleeAttackOneEndComponent>(*this);
}

bool ratchet::PlayerMeleeAttackOneEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackOneEndState);
    return true;
}