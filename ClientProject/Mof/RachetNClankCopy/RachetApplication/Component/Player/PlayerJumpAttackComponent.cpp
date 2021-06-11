#include "PlayerJumpAttackComponent.h"

#include "PlayerOmniWrenchComponent.h"


rachet::PlayerJumpAttackComponent::PlayerJumpAttackComponent(int priority) :
    super(priority),
    _down_speed(7.0f),
    _weapon_com() {
}

rachet::PlayerJumpAttackComponent::PlayerJumpAttackComponent(const PlayerJumpAttackComponent& obj) :
    super(obj),
    _down_speed(obj._down_speed),
    _weapon_com() {
}

rachet::PlayerJumpAttackComponent::~PlayerJumpAttackComponent() {
}

std::string rachet::PlayerJumpAttackComponent::GetType(void) const {
    return "PlayerJumpAttackComponent";
}

std::string_view rachet::PlayerJumpAttackComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpAttackState;
}

bool rachet::PlayerJumpAttackComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<rachet::PlayerOmniWrenchComponent>();
    return true;
}

bool rachet::PlayerJumpAttackComponent::Input(void) {
    return false;
}

bool rachet::PlayerJumpAttackComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if

    auto velocity_com = super::GetVelocityComponent();
    auto velocity = Mof::CVector3(0.0f, -_down_speed, 0.0f);
    velocity_com->AddVelocityForce(velocity);
    return true;
}

bool rachet::PlayerJumpAttackComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerJumpAttackComponent::Clone(void) {
    return std::make_shared<rachet::PlayerJumpAttackComponent>(*this);
}

bool rachet::PlayerJumpAttackComponent::Start(void) {
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

bool rachet::PlayerJumpAttackComponent::End(void) {
    super::End();
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    return true;
}