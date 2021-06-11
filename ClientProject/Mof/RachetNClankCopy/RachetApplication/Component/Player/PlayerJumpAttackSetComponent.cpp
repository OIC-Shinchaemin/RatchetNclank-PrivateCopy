#include "PlayerJumpAttackSetComponent.h"

#include "PlayerOmniWrenchComponent.h"


rachet::PlayerJumpAttackSetComponent::PlayerJumpAttackSetComponent(int priority) :
    super(priority),
    _up_speed(5.0f),
    _weapon_com() {
}

rachet::PlayerJumpAttackSetComponent::PlayerJumpAttackSetComponent(const PlayerJumpAttackSetComponent& obj) :
    super(obj),
    _up_speed(obj._up_speed),
    _weapon_com() {
}

rachet::PlayerJumpAttackSetComponent::~PlayerJumpAttackSetComponent() {
}

std::string rachet::PlayerJumpAttackSetComponent::GetType(void) const {
    return "PlayerJumpAttackSetComponent";
}

std::string_view rachet::PlayerJumpAttackSetComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpAttackSetState;
}

bool rachet::PlayerJumpAttackSetComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<rachet::PlayerOmniWrenchComponent>();
    return true;
}

bool rachet::PlayerJumpAttackSetComponent::Input(void) {
    return false;
}

bool rachet::PlayerJumpAttackSetComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpAttackState);
    } // if

    auto velocity_com = super::GetVelocityComponent();
    auto velocity = Mof::CVector3(0.0f, _up_speed, 0.0f);
    velocity_com->AddVelocityForce(velocity);
    return true;
}

bool rachet::PlayerJumpAttackSetComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerJumpAttackSetComponent::Clone(void) {
    return std::make_shared<rachet::PlayerJumpAttackSetComponent>(*this);
}

bool rachet::PlayerJumpAttackSetComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionJumpAttackSetState);
    return true;
}