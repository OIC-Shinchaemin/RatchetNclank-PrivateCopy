#include "PlayerJumpAttackSetComponent.h"

#include "PlayerOmniWrenchComponent.h"


ratchet::PlayerJumpAttackSetComponent::PlayerJumpAttackSetComponent(int priority) :
    super(priority),
    _up_speed(5.0f),
    _weapon_com() {
}

ratchet::PlayerJumpAttackSetComponent::PlayerJumpAttackSetComponent(const PlayerJumpAttackSetComponent& obj) :
    super(obj),
    _up_speed(obj._up_speed),
    _weapon_com() {
}

ratchet::PlayerJumpAttackSetComponent::~PlayerJumpAttackSetComponent() {
}

std::string ratchet::PlayerJumpAttackSetComponent::GetType(void) const {
    return "PlayerJumpAttackSetComponent";
}

std::string_view ratchet::PlayerJumpAttackSetComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpAttackSetState;
}

bool ratchet::PlayerJumpAttackSetComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<ratchet::PlayerOmniWrenchComponent>();
    return true;
}

bool ratchet::PlayerJumpAttackSetComponent::Input(void) {
    return false;
}

bool ratchet::PlayerJumpAttackSetComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpAttackState);
    } // if

    auto velocity_com = super::GetVelocityComponent();
    auto velocity = Mof::CVector3(0.0f, _up_speed, 0.0f);
    velocity_com->AddVelocityForce(velocity);
    return true;
}

bool ratchet::PlayerJumpAttackSetComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerJumpAttackSetComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerJumpAttackSetComponent>(*this);
}

bool ratchet::PlayerJumpAttackSetComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionJumpAttackSetState);
    return true;
}