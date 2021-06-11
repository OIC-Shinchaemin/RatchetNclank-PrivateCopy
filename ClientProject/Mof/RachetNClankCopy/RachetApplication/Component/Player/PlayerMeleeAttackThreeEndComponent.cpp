#include "PlayerMeleeAttackThreeEndComponent.h"


rachet::PlayerMeleeAttackThreeEndComponent::PlayerMeleeAttackThreeEndComponent(int priority) :
    super(priority) {
}

rachet::PlayerMeleeAttackThreeEndComponent::PlayerMeleeAttackThreeEndComponent(const PlayerMeleeAttackThreeEndComponent& obj) :
    super(obj) {
}

rachet::PlayerMeleeAttackThreeEndComponent::~PlayerMeleeAttackThreeEndComponent() {
}

std::string rachet::PlayerMeleeAttackThreeEndComponent::GetType(void) const {
    return "PlayerMeleeAttackThreeEndComponent";
}

std::string_view rachet::PlayerMeleeAttackThreeEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackThreeEndState;
}

bool rachet::PlayerMeleeAttackThreeEndComponent::Input(void) {
    return false;
}

bool rachet::PlayerMeleeAttackThreeEndComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerMeleeAttackThreeEndComponent::Clone(void) {
    return std::make_shared<rachet::PlayerMeleeAttackThreeEndComponent>(*this);
}

bool rachet::PlayerMeleeAttackThreeEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackThreeEndState);
    return true;
}