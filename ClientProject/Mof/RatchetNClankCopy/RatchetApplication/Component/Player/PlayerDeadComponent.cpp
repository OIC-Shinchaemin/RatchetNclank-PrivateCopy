#include "PlayerDeadComponent.h"


ratchet::component::player::action::PlayerDeadComponent::PlayerDeadComponent(int priority) :
    super(priority) {
}

ratchet::component::player::action::PlayerDeadComponent::PlayerDeadComponent(const PlayerDeadComponent& obj) :
    super(obj) {
}

ratchet::component::player::action::PlayerDeadComponent::~PlayerDeadComponent() {
}

std::string ratchet::component::player::action::PlayerDeadComponent::GetType(void) const {
    return "PlayerDeadComponent";
}

std::string_view ratchet::component::player::action::PlayerDeadComponent::GetStateType(void) const {
    return ratchet::state::PlayerActionStateType::kPlayerActionDeadState;
}

bool ratchet::component::player::action::PlayerDeadComponent::Input(void) {
    return false;
}

bool ratchet::component::player::action::PlayerDeadComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::GetOwner()->Notify("PlayerDead", super::GetOwner());
    } // if
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerDeadComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerDeadComponent>(*this);
}

bool ratchet::component::player::action::PlayerDeadComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(ratchet::state::PlayerMotionStateType::kPlayerMotionDeadState);
    return true;
}