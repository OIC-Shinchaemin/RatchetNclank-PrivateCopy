#include "PlayerLookComponent.h"


rachet::PlayerLookComponent::PlayerLookComponent(int priority) :
    super(priority) {
}

rachet::PlayerLookComponent::PlayerLookComponent(const PlayerLookComponent& obj) :
    super(obj) {
}

rachet::PlayerLookComponent::~PlayerLookComponent() {
}

std::string rachet::PlayerLookComponent::GetType(void) const {
    return "PlayerLookComponent";
}

std::string_view rachet::PlayerLookComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionLookState;
}

bool rachet::PlayerLookComponent::Input(void) {
    return false;
}

bool rachet::PlayerLookComponent::Update(float delta_time) {
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerLookComponent::Clone(void) {
    return std::make_shared<rachet::PlayerLookComponent>(*this);
}

bool rachet::PlayerLookComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionIdleState);
    return true;
}