#include "PlayerMeleeAttackThreeEndComponent.h"


ratchet::PlayerMeleeAttackThreeEndComponent::PlayerMeleeAttackThreeEndComponent(int priority) :
    super(priority) {
}

ratchet::PlayerMeleeAttackThreeEndComponent::PlayerMeleeAttackThreeEndComponent(const PlayerMeleeAttackThreeEndComponent& obj) :
    super(obj) {
}

ratchet::PlayerMeleeAttackThreeEndComponent::~PlayerMeleeAttackThreeEndComponent() {
}

std::string ratchet::PlayerMeleeAttackThreeEndComponent::GetType(void) const {
    return "PlayerMeleeAttackThreeEndComponent";
}

std::string_view ratchet::PlayerMeleeAttackThreeEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackThreeEndState;
}

bool ratchet::PlayerMeleeAttackThreeEndComponent::Input(void) {
    return false;
}

bool ratchet::PlayerMeleeAttackThreeEndComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::PlayerMeleeAttackThreeEndComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerMeleeAttackThreeEndComponent>(*this);
}

bool ratchet::PlayerMeleeAttackThreeEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackThreeEndState);
    return true;
}