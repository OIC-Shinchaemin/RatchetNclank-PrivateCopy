#include "PlayerThrowAttackEndComponent.h"

#include "PlayerOmniWrenchComponent.h"


ratchet::component::player::action::PlayerThrowAttackEndComponent::PlayerThrowAttackEndComponent(int priority) :
    super(priority),
    _weapon_com() {
}

ratchet::component::player::action::PlayerThrowAttackEndComponent::PlayerThrowAttackEndComponent(const PlayerThrowAttackEndComponent& obj) :
    super(obj),
    _weapon_com() {
}

ratchet::component::player::action::PlayerThrowAttackEndComponent::~PlayerThrowAttackEndComponent() {
}

std::string ratchet::component::player::action::PlayerThrowAttackEndComponent::GetType(void) const {
    return "PlayerThrowAttackEndComponent";
}

std::string_view ratchet::component::player::action::PlayerThrowAttackEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackEndState;
}

bool ratchet::component::player::action::PlayerThrowAttackEndComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<ratchet::component::player::PlayerOmniWrenchComponent>();
    return true;
}

bool ratchet::component::player::action::PlayerThrowAttackEndComponent::Input(void) {
    return false;
}

bool ratchet::component::player::action::PlayerThrowAttackEndComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

bool ratchet::component::player::action::PlayerThrowAttackEndComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerThrowAttackEndComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerThrowAttackEndComponent>(*this);
}

bool ratchet::component::player::action::PlayerThrowAttackEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionThrowAttackEndState);
    return true;
}