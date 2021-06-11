#include "PlayerDeadComponent.h"


ratchet::PlayerDeadComponent::PlayerDeadComponent(int priority) :
    super(priority) {
}

ratchet::PlayerDeadComponent::PlayerDeadComponent(const PlayerDeadComponent& obj) :
    super(obj) {
}

ratchet::PlayerDeadComponent::~PlayerDeadComponent() {
}

std::string ratchet::PlayerDeadComponent::GetType(void) const {
    return "PlayerDeadComponent";
}

std::string_view ratchet::PlayerDeadComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionDeadState;
}

bool ratchet::PlayerDeadComponent::Input(void) {
    return false;
}

bool ratchet::PlayerDeadComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::GetOwner()->Notify("PlayerDead", super::GetOwner());
    } // if
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::PlayerDeadComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerDeadComponent>(*this);
}

bool ratchet::PlayerDeadComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionDeadState);
    return true;
}