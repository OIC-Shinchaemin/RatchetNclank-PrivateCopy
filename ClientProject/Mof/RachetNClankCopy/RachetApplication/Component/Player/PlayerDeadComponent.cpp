#include "PlayerDeadComponent.h"


my::PlayerDeadComponent::PlayerDeadComponent(int priority) :
    super(priority) {
}

my::PlayerDeadComponent::PlayerDeadComponent(const PlayerDeadComponent& obj) :
    super(obj) {
}

my::PlayerDeadComponent::~PlayerDeadComponent() {
}

std::string my::PlayerDeadComponent::GetType(void) const {
    return "PlayerDeadComponent";
}

std::string_view my::PlayerDeadComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionDeadState;
}

bool my::PlayerDeadComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::GetOwner()->End();
    } // if
    return true;
}

std::shared_ptr<my::Component> my::PlayerDeadComponent::Clone(void) {
    return std::make_shared<my::PlayerDeadComponent>(*this);
}

bool my::PlayerDeadComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionDeadState);
    return true;
}