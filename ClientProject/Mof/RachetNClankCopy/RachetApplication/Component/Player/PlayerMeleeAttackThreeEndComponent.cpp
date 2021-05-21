#include "PlayerMeleeAttackThreeEndComponent.h"


my::PlayerMeleeAttackThreeEndComponent::PlayerMeleeAttackThreeEndComponent(int priority) :
    super(priority) {
}

my::PlayerMeleeAttackThreeEndComponent::PlayerMeleeAttackThreeEndComponent(const PlayerMeleeAttackThreeEndComponent& obj) :
    super(obj) {
}

my::PlayerMeleeAttackThreeEndComponent::~PlayerMeleeAttackThreeEndComponent() {
}

std::string my::PlayerMeleeAttackThreeEndComponent::GetType(void) const {
    return "PlayerMeleeAttackThreeEndComponent";
}

std::string_view my::PlayerMeleeAttackThreeEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackThreeEndState;
}

bool my::PlayerMeleeAttackThreeEndComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

std::shared_ptr<my::Component> my::PlayerMeleeAttackThreeEndComponent::Clone(void) {
    return std::make_shared<my::PlayerMeleeAttackThreeEndComponent>(*this);
}

bool my::PlayerMeleeAttackThreeEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackThreeEndState);
    return true;
}