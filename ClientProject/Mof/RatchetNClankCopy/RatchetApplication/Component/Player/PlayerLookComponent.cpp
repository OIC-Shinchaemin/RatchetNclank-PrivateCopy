#include "PlayerLookComponent.h"


ratchet::PlayerLookComponent::PlayerLookComponent(int priority) :
    super(priority) {
}

ratchet::PlayerLookComponent::PlayerLookComponent(const PlayerLookComponent& obj) :
    super(obj) {
}

ratchet::PlayerLookComponent::~PlayerLookComponent() {
}

std::string ratchet::PlayerLookComponent::GetType(void) const {
    return "PlayerLookComponent";
}

std::string_view ratchet::PlayerLookComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionLookState;
}

bool ratchet::PlayerLookComponent::Input(void) {
    return false;
}

bool ratchet::PlayerLookComponent::Update(float delta_time) {
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerLookComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerLookComponent>(*this);
}

bool ratchet::PlayerLookComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionIdleState);
    return true;
}