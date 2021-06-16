#include "PlayerMeleeAttackTwoEndComponent.h"


ratchet::component::player::action::PlayerMeleeAttackTwoEndComponent::PlayerMeleeAttackTwoEndComponent(int priority) :
    super(priority) {
}

ratchet::component::player::action::PlayerMeleeAttackTwoEndComponent::PlayerMeleeAttackTwoEndComponent(const PlayerMeleeAttackTwoEndComponent& obj) :
    super(obj) {
}

ratchet::component::player::action::PlayerMeleeAttackTwoEndComponent::~PlayerMeleeAttackTwoEndComponent() {
}

std::string ratchet::component::player::action::PlayerMeleeAttackTwoEndComponent::GetType(void) const {
    return "PlayerMeleeAttackTwoEndComponent";
}

std::string_view ratchet::component::player::action::PlayerMeleeAttackTwoEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackTwoEndState;
}

bool ratchet::component::player::action::PlayerMeleeAttackTwoEndComponent::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_N) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMeleeAttackThreeState);
    } // if

    return true;
}

bool ratchet::component::player::action::PlayerMeleeAttackTwoEndComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerMeleeAttackTwoEndComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerMeleeAttackTwoEndComponent>(*this);
}

bool ratchet::component::player::action::PlayerMeleeAttackTwoEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackTwoEndState);
    return true;
}