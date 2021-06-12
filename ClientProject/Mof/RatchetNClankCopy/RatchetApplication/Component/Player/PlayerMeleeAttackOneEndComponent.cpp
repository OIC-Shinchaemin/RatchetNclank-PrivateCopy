#include "PlayerMeleeAttackOneEndComponent.h"


ratchet::component::player::action::PlayerMeleeAttackOneEndComponent::PlayerMeleeAttackOneEndComponent(int priority) :
    super(priority) {
}

ratchet::component::player::action::PlayerMeleeAttackOneEndComponent::PlayerMeleeAttackOneEndComponent(const PlayerMeleeAttackOneEndComponent& obj) :
    super(obj) {
}

ratchet::component::player::action::PlayerMeleeAttackOneEndComponent::~PlayerMeleeAttackOneEndComponent() {
}

std::string ratchet::component::player::action::PlayerMeleeAttackOneEndComponent::GetType(void) const {
    return "PlayerMeleeAttackOneEndComponent";
}

std::string_view ratchet::component::player::action::PlayerMeleeAttackOneEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackOneEndState;
}

bool ratchet::component::player::action::PlayerMeleeAttackOneEndComponent::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_N) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMeleeAttackTwoState);
    } // if
    return true;
}

bool ratchet::component::player::action::PlayerMeleeAttackOneEndComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerMeleeAttackOneEndComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerMeleeAttackOneEndComponent>(*this);
}

bool ratchet::component::player::action::PlayerMeleeAttackOneEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackOneEndState);
    return true;
}