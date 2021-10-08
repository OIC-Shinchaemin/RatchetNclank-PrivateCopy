#include "PlayerJumpAttackComponent.h"

#include "PlayerOmniWrenchComponent.h"


ratchet::component::player::action::PlayerJumpAttackComponent::PlayerJumpAttackComponent(int priority) :
    super(priority),
    _down_speed(4.0f),
    _weapon_com() {
}

ratchet::component::player::action::PlayerJumpAttackComponent::PlayerJumpAttackComponent(const PlayerJumpAttackComponent& obj) :
    super(obj),
    _down_speed(obj._down_speed),
    _weapon_com() {
}

ratchet::component::player::action::PlayerJumpAttackComponent::~PlayerJumpAttackComponent() {
}

std::string ratchet::component::player::action::PlayerJumpAttackComponent::GetType(void) const {
    return "PlayerJumpAttackComponent";
}

std::string_view ratchet::component::player::action::PlayerJumpAttackComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpAttackState;
}

bool ratchet::component::player::action::PlayerJumpAttackComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<ratchet::component::player::PlayerOmniWrenchComponent>();
    return true;
}

bool ratchet::component::player::action::PlayerJumpAttackComponent::Input(void) {
    return false;
}

bool ratchet::component::player::action::PlayerJumpAttackComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if

    auto velocity_com = super::GetVelocityComponent();
    auto velocity = Mof::CVector3(0.0f, -_down_speed, 0.0f);
    velocity_com->AddVelocityForce(velocity);
    return true;
}

bool ratchet::component::player::action::PlayerJumpAttackComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerJumpAttackComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerJumpAttackComponent>(*this);
}

bool ratchet::component::player::action::PlayerJumpAttackComponent::Start(void) {
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

bool ratchet::component::player::action::PlayerJumpAttackComponent::End(void) {
    super::End();
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    return true;
}