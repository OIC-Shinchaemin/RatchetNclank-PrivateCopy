#include "PlayerJumpAttackSetComponent.h"

#include "PlayerWeaponComponent.h"


my::PlayerJumpAttackSetComponent::PlayerJumpAttackSetComponent(int priority) :
    super(priority),
    _up_speed(5.0f),
    _weapon_com() {
}

my::PlayerJumpAttackSetComponent::PlayerJumpAttackSetComponent(const PlayerJumpAttackSetComponent& obj) :
    super(obj),
    _up_speed(obj._up_speed),
    _weapon_com() {
}

my::PlayerJumpAttackSetComponent::~PlayerJumpAttackSetComponent() {
}

std::string my::PlayerJumpAttackSetComponent::GetType(void) const {
    return "PlayerJumpAttackSetComponent";
}

std::string_view my::PlayerJumpAttackSetComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpAttackSetState;
}

bool my::PlayerJumpAttackSetComponent::Initialize(void) {
    super::Initialize();
    _weapon_com = super::GetOwner()->GetComponent<my::PlayerWeaponComponent>();
    return true;
}

bool my::PlayerJumpAttackSetComponent::Update(float delta_time) {
    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpAttackState);
    } // if

    auto velocity_com = super::GetVelocityComponent();
    auto velocity = Mof::CVector3(0.0f, _up_speed, 0.0f);
    velocity_com->AddVelocityForce(velocity);
    return true;
}

bool my::PlayerJumpAttackSetComponent::Release(void) {
    super::Release();
    _weapon_com.reset();
    return true;
}

std::shared_ptr<my::Component> my::PlayerJumpAttackSetComponent::Clone(void) {
    return std::make_shared<my::PlayerJumpAttackSetComponent>(*this);
}

bool my::PlayerJumpAttackSetComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionJumpAttackSetState);
    return true;
}