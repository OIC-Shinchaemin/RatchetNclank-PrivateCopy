#include "PlayerJumpAttackComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"
#include "PlayerMoveComponent.h"
#include "PlayerWeaponComponent.h"


void my::PlayerJumpAttackComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::PlayerJumpAttackComponent::PlayerJumpAttackComponent(int priority) :
    super(priority),
    _down_speed(7.0f),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com(),
    _weapon_com() {
}

my::PlayerJumpAttackComponent::PlayerJumpAttackComponent(const PlayerJumpAttackComponent& obj) :
    super(obj),
    _down_speed(obj._down_speed),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com(),
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
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    _weapon_com = super::GetOwner()->GetComponent<my::PlayerWeaponComponent>();
    return true;
}

bool my::PlayerJumpAttackComponent::Update(float delta_time) {
    auto motion_com = _motion_com.lock();
    if (motion_com->IsEndMotion()) {
        this->ChageState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if

    if (auto velocity_com = _velocity_com.lock()) {
        auto velocity = Mof::CVector3(0.0f, -_down_speed, 0.0f);
        velocity_com->AddVelocityForce(velocity);
    } // if
    return true;
}

bool my::PlayerJumpAttackComponent::Release(void) {
    super::Release();
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
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionJumpAttackState);
    } // if
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