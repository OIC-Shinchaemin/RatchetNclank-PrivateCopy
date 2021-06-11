#include "PlayerMeleeAttackTwoEndComponent.h"


ratchet::PlayerMeleeAttackTwoEndComponent::PlayerMeleeAttackTwoEndComponent(int priority) :
    super(priority) {
}

ratchet::PlayerMeleeAttackTwoEndComponent::PlayerMeleeAttackTwoEndComponent(const PlayerMeleeAttackTwoEndComponent& obj) :
    super(obj) {
}

ratchet::PlayerMeleeAttackTwoEndComponent::~PlayerMeleeAttackTwoEndComponent() {
}

std::string ratchet::PlayerMeleeAttackTwoEndComponent::GetType(void) const {
    return "PlayerMeleeAttackTwoEndComponent";
}

std::string_view ratchet::PlayerMeleeAttackTwoEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackTwoEndState;
}

bool ratchet::PlayerMeleeAttackTwoEndComponent::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_N) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMeleeAttackThreeState);
    } // if

    return true;
}

bool ratchet::PlayerMeleeAttackTwoEndComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerMeleeAttackTwoEndComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerMeleeAttackTwoEndComponent>(*this);
}

bool ratchet::PlayerMeleeAttackTwoEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackTwoEndState);
    return true;
}