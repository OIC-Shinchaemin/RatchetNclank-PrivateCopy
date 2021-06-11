#include "PlayerMeleeAttackTwoEndComponent.h"


rachet::PlayerMeleeAttackTwoEndComponent::PlayerMeleeAttackTwoEndComponent(int priority) :
    super(priority) {
}

rachet::PlayerMeleeAttackTwoEndComponent::PlayerMeleeAttackTwoEndComponent(const PlayerMeleeAttackTwoEndComponent& obj) :
    super(obj) {
}

rachet::PlayerMeleeAttackTwoEndComponent::~PlayerMeleeAttackTwoEndComponent() {
}

std::string rachet::PlayerMeleeAttackTwoEndComponent::GetType(void) const {
    return "PlayerMeleeAttackTwoEndComponent";
}

std::string_view rachet::PlayerMeleeAttackTwoEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackTwoEndState;
}

bool rachet::PlayerMeleeAttackTwoEndComponent::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_N) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMeleeAttackThreeState);
    } // if

    return true;
}

bool rachet::PlayerMeleeAttackTwoEndComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerMeleeAttackTwoEndComponent::Clone(void) {
    return std::make_shared<rachet::PlayerMeleeAttackTwoEndComponent>(*this);
}

bool rachet::PlayerMeleeAttackTwoEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackTwoEndState);
    return true;
}