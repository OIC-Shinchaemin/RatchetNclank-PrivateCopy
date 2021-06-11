#include "PlayerDeadComponent.h"


rachet::PlayerDeadComponent::PlayerDeadComponent(int priority) :
    super(priority) {
}

rachet::PlayerDeadComponent::PlayerDeadComponent(const PlayerDeadComponent& obj) :
    super(obj) {
}

rachet::PlayerDeadComponent::~PlayerDeadComponent() {
}

std::string rachet::PlayerDeadComponent::GetType(void) const {
    return "PlayerDeadComponent";
}

std::string_view rachet::PlayerDeadComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionDeadState;
}

bool rachet::PlayerDeadComponent::Input(void) {
    return false;
}

bool rachet::PlayerDeadComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::GetOwner()->Notify("PlayerDead", super::GetOwner());
    } // if
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerDeadComponent::Clone(void) {
    return std::make_shared<rachet::PlayerDeadComponent>(*this);
}

bool rachet::PlayerDeadComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionDeadState);
    return true;
}