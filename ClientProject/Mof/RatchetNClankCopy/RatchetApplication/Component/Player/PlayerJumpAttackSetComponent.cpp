#include "PlayerJumpAttackSetComponent.h"

#include "PlayerOmniWrenchComponent.h"


ratchet::component::player::action::PlayerJumpAttackSetComponent::PlayerJumpAttackSetComponent(int priority) :
    super(priority),
    _up_speed(4.0f),
    _weapon_com() {
}

ratchet::component::player::action::PlayerJumpAttackSetComponent::PlayerJumpAttackSetComponent(const PlayerJumpAttackSetComponent& obj) :
    super(obj),
    _up_speed(obj._up_speed),
    _weapon_com() {
}

ratchet::component::player::action::PlayerJumpAttackSetComponent::~PlayerJumpAttackSetComponent() {
}

std::string ratchet::component::player::action::PlayerJumpAttackSetComponent::GetType(void) const {
    return "PlayerJumpAttackSetComponent";
}

std::string_view ratchet::component::player::action::PlayerJumpAttackSetComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpAttackSetState;
}

bool ratchet::component::player::action::PlayerJumpAttackSetComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<ratchet::component::player::PlayerOmniWrenchComponent>();
    return true;
}

bool ratchet::component::player::action::PlayerJumpAttackSetComponent::Input(void) {
    return false;
}

bool ratchet::component::player::action::PlayerJumpAttackSetComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpAttackState);
    } // if

    auto velocity_com = super::GetVelocityComponent();
    auto velocity = Mof::CVector3(0.0f, _up_speed, 0.0f);
    velocity_com->AddVelocityForce(velocity);
    return true;
}

bool ratchet::component::player::action::PlayerJumpAttackSetComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerJumpAttackSetComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerJumpAttackSetComponent>(*this);
}

bool ratchet::component::player::action::PlayerJumpAttackSetComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionJumpAttackSetState);
    return true;
}