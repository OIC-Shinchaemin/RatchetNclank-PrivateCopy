#include "PlayerMeleeAttackOneEndComponent.h"


my::PlayerMeleeAttackOneEndComponent::PlayerMeleeAttackOneEndComponent(int priority) :
    super(priority) {
}

my::PlayerMeleeAttackOneEndComponent::PlayerMeleeAttackOneEndComponent(const PlayerMeleeAttackOneEndComponent& obj) :
    super(obj) {
}

my::PlayerMeleeAttackOneEndComponent::~PlayerMeleeAttackOneEndComponent() {
}

std::string my::PlayerMeleeAttackOneEndComponent::GetType(void) const {
    return "PlayerMeleeAttackOneEndComponent";
}

std::string_view my::PlayerMeleeAttackOneEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackOneEndState;
}

bool my::PlayerMeleeAttackOneEndComponent::Input(void) {
    return false;
}

bool my::PlayerMeleeAttackOneEndComponent::Update(float delta_time) {
    if (::g_pInput->IsKeyPush(MOFKEY_Z) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMeleeAttackTwoState);
    } // if

    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

std::shared_ptr<my::Component> my::PlayerMeleeAttackOneEndComponent::Clone(void) {
    return std::make_shared<my::PlayerMeleeAttackOneEndComponent>(*this);
}

bool my::PlayerMeleeAttackOneEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackOneEndState);
    return true;
}