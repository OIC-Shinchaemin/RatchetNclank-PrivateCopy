#include "PlayerJumpAttackComponent.h"

#include "PlayerOmniWrenchComponent.h"


ratchet::PlayerJumpAttackComponent::PlayerJumpAttackComponent(int priority) :
    super(priority),
    _down_speed(7.0f),
    _weapon_com() {
}

ratchet::PlayerJumpAttackComponent::PlayerJumpAttackComponent(const PlayerJumpAttackComponent& obj) :
    super(obj),
    _down_speed(obj._down_speed),
    _weapon_com() {
}

ratchet::PlayerJumpAttackComponent::~PlayerJumpAttackComponent() {
}

std::string ratchet::PlayerJumpAttackComponent::GetType(void) const {
    return "PlayerJumpAttackComponent";
}

std::string_view ratchet::PlayerJumpAttackComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpAttackState;
}

bool ratchet::PlayerJumpAttackComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<ratchet::PlayerOmniWrenchComponent>();
    return true;
}

bool ratchet::PlayerJumpAttackComponent::Input(void) {
    return false;
}

bool ratchet::PlayerJumpAttackComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if

    auto velocity_com = super::GetVelocityComponent();
    auto velocity = Mof::CVector3(0.0f, -_down_speed, 0.0f);
    velocity_com->AddVelocityForce(velocity);
    return true;
}

bool ratchet::PlayerJumpAttackComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::PlayerJumpAttackComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerJumpAttackComponent>(*this);
}

bool ratchet::PlayerJumpAttackComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionJumpAttackState);

    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Activate();
    } // if
    return true;
}

bool ratchet::PlayerJumpAttackComponent::End(void) {
    super::End();
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    return true;
}