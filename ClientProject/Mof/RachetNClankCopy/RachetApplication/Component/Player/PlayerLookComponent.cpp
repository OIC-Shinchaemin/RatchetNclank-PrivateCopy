#include "PlayerLookComponent.h"


my::PlayerLookComponent::PlayerLookComponent(int priority) :
    super(priority) {
}

my::PlayerLookComponent::PlayerLookComponent(const PlayerLookComponent& obj) :
    super(obj) {
}

my::PlayerLookComponent::~PlayerLookComponent() {
}

std::string my::PlayerLookComponent::GetType(void) const {
    return "PlayerLookComponent";
}

std::string_view my::PlayerLookComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionLookState;
}

bool my::PlayerLookComponent::Update(float delta_time) {
    return true;
}

std::shared_ptr<my::Component> my::PlayerLookComponent::Clone(void) {
    return std::make_shared<my::PlayerLookComponent>(*this);
}

bool my::PlayerLookComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionIdleState);
    return true;
}