#include "PlayerMeleeAttackTwoEndComponent.h"


my::PlayerMeleeAttackTwoEndComponent::PlayerMeleeAttackTwoEndComponent(int priority) :
    super(priority) {
}

my::PlayerMeleeAttackTwoEndComponent::PlayerMeleeAttackTwoEndComponent(const PlayerMeleeAttackTwoEndComponent& obj) :
    super(obj) {
}

my::PlayerMeleeAttackTwoEndComponent::~PlayerMeleeAttackTwoEndComponent() {
}

std::string my::PlayerMeleeAttackTwoEndComponent::GetType(void) const {
    return "PlayerMeleeAttackTwoEndComponent";
}

std::string_view my::PlayerMeleeAttackTwoEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackTwoEndState;
}

bool my::PlayerMeleeAttackTwoEndComponent::Update(float delta_time) {
    if (::g_pInput->IsKeyPush(MOFKEY_Z) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMeleeAttackThreeState);
    } // if

    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

std::shared_ptr<my::Component> my::PlayerMeleeAttackTwoEndComponent::Clone(void) {
    return std::make_shared<my::PlayerMeleeAttackTwoEndComponent>(*this);
}

bool my::PlayerMeleeAttackTwoEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackTwoEndState);
    return true;
}