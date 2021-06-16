#include "PlayerThrowAttackSetComponent.h"

#include "PlayerOmniWrenchComponent.h"


ratchet::component::player::action::PlayerThrowAttackSetComponent::PlayerThrowAttackSetComponent(int priority) :
    super(priority),
    _weapon_com() {
}

ratchet::component::player::action::PlayerThrowAttackSetComponent::PlayerThrowAttackSetComponent(const PlayerThrowAttackSetComponent& obj) :
    super(obj),
    _weapon_com() {
}

ratchet::component::player::action::PlayerThrowAttackSetComponent::~PlayerThrowAttackSetComponent() {
}

std::string ratchet::component::player::action::PlayerThrowAttackSetComponent::GetType(void) const {
    return "PlayerThrowAttackSetComponent";
}

std::string_view ratchet::component::player::action::PlayerThrowAttackSetComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackSetState;
}

bool ratchet::component::player::action::PlayerThrowAttackSetComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<ratchet::component::player::PlayerOmniWrenchComponent>();
    return true;
}

bool ratchet::component::player::action::PlayerThrowAttackSetComponent::Input(void) {
    return false;
}

bool ratchet::component::player::action::PlayerThrowAttackSetComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionThrowAttackState);
    } // if
    return true;
}

bool ratchet::component::player::action::PlayerThrowAttackSetComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerThrowAttackSetComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerThrowAttackSetComponent>(*this);
}

bool ratchet::component::player::action::PlayerThrowAttackSetComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionThrowAttackSetState);
    return true;
}