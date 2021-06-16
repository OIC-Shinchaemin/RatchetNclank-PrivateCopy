#include "PlayerLookComponent.h"


ratchet::component::player::action::PlayerLookComponent::PlayerLookComponent(int priority) :
    super(priority) {
}

ratchet::component::player::action::PlayerLookComponent::PlayerLookComponent(const PlayerLookComponent& obj) :
    super(obj) {
}

ratchet::component::player::action::PlayerLookComponent::~PlayerLookComponent() {
}

std::string ratchet::component::player::action::PlayerLookComponent::GetType(void) const {
    return "PlayerLookComponent";
}

std::string_view ratchet::component::player::action::PlayerLookComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionLookState;
}

bool ratchet::component::player::action::PlayerLookComponent::Input(void) {
    return false;
}

bool ratchet::component::player::action::PlayerLookComponent::Update(float delta_time) {
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerLookComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerLookComponent>(*this);
}

bool ratchet::component::player::action::PlayerLookComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionIdleState);
    return true;
}