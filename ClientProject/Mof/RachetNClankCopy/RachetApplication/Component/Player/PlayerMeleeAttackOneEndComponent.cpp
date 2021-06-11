#include "PlayerMeleeAttackOneEndComponent.h"


rachet::PlayerMeleeAttackOneEndComponent::PlayerMeleeAttackOneEndComponent(int priority) :
    super(priority) {
}

rachet::PlayerMeleeAttackOneEndComponent::PlayerMeleeAttackOneEndComponent(const PlayerMeleeAttackOneEndComponent& obj) :
    super(obj) {
}

rachet::PlayerMeleeAttackOneEndComponent::~PlayerMeleeAttackOneEndComponent() {
}

std::string rachet::PlayerMeleeAttackOneEndComponent::GetType(void) const {
    return "PlayerMeleeAttackOneEndComponent";
}

std::string_view rachet::PlayerMeleeAttackOneEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackOneEndState;
}

bool rachet::PlayerMeleeAttackOneEndComponent::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_N) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMeleeAttackTwoState);
    } // if
    return true;
}

bool rachet::PlayerMeleeAttackOneEndComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerMeleeAttackOneEndComponent::Clone(void) {
    return std::make_shared<rachet::PlayerMeleeAttackOneEndComponent>(*this);
}

bool rachet::PlayerMeleeAttackOneEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackOneEndState);
    return true;
}