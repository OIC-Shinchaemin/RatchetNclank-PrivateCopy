#include "PlayerJumpAttackComponent.h"

#include "PlayerOmniWrenchComponent.h"


my::PlayerJumpAttackComponent::PlayerJumpAttackComponent(int priority) :
    super(priority),
    _down_speed(7.0f),
    _weapon_com() {
}

my::PlayerJumpAttackComponent::PlayerJumpAttackComponent(const PlayerJumpAttackComponent& obj) :
    super(obj),
    _down_speed(obj._down_speed),
    _weapon_com() {
}

my::PlayerJumpAttackComponent::~PlayerJumpAttackComponent() {
}

std::string my::PlayerJumpAttackComponent::GetType(void) const {
    return "PlayerJumpAttackComponent";
}

std::string_view my::PlayerJumpAttackComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpAttackState;
}

bool my::PlayerJumpAttackComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<my::PlayerOmniWrenchComponent>();
    return true;
}

bool my::PlayerJumpAttackComponent::Input(void) {
    return false;
}

bool my::PlayerJumpAttackComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if

    auto velocity_com = super::GetVelocityComponent();
    auto velocity = Mof::CVector3(0.0f, -_down_speed, 0.0f);
    velocity_com->AddVelocityForce(velocity);
    return true;
}

bool my::PlayerJumpAttackComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<my::Component> my::PlayerJumpAttackComponent::Clone(void) {
    return std::make_shared<my::PlayerJumpAttackComponent>(*this);
}

bool my::PlayerJumpAttackComponent::Start(void) {
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

bool my::PlayerJumpAttackComponent::End(void) {
    super::End();
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    return true;
}