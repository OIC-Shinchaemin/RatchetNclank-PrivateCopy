#include "PlayerMeleeAttackThreeEndComponent.h"


ratchet::component::player::action::PlayerMeleeAttackThreeEndComponent::PlayerMeleeAttackThreeEndComponent(int priority) :
    super(priority) {
}

ratchet::component::player::action::PlayerMeleeAttackThreeEndComponent::PlayerMeleeAttackThreeEndComponent(const PlayerMeleeAttackThreeEndComponent& obj) :
    super(obj) {
}

ratchet::component::player::action::PlayerMeleeAttackThreeEndComponent::~PlayerMeleeAttackThreeEndComponent() {
}

std::string ratchet::component::player::action::PlayerMeleeAttackThreeEndComponent::GetType(void) const {
    return "PlayerMeleeAttackThreeEndComponent";
}

std::string_view ratchet::component::player::action::PlayerMeleeAttackThreeEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackThreeEndState;
}

bool ratchet::component::player::action::PlayerMeleeAttackThreeEndComponent::Input(void) {
    return false;
}

bool ratchet::component::player::action::PlayerMeleeAttackThreeEndComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerMeleeAttackThreeEndComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerMeleeAttackThreeEndComponent>(*this);
}

bool ratchet::component::player::action::PlayerMeleeAttackThreeEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackThreeEndState);
    return true;
}