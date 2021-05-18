#include "PlayerJumpAttackSetComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"
#include "PlayerMoveComponent.h"
#include "PlayerWeaponComponent.h"



void my::PlayerJumpAttackSetComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::PlayerJumpAttackSetComponent::PlayerJumpAttackSetComponent(int priority) :
    super(priority),
    _up_speed(5.0f),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com(),
    _weapon_com() {
}

my::PlayerJumpAttackSetComponent::PlayerJumpAttackSetComponent(const PlayerJumpAttackSetComponent& obj) :
    super(obj),
    _up_speed(obj._up_speed),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com(),
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
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    _weapon_com = super::GetOwner()->GetComponent<my::PlayerWeaponComponent>();
    return true;
}

bool my::PlayerJumpAttackSetComponent::Update(float delta_time) {
    auto motion_com = _motion_com.lock();
    if (motion_com->IsEndMotion()) {
        this->ChageState(state::PlayerActionStateType::kPlayerActionJumpAttackState);
    } // if
    
    if (auto velocity_com = _velocity_com.lock()) {
        auto velocity = Mof::CVector3(0.0f, _up_speed, 0.0f);
        velocity_com->AddVelocityForce(velocity);
    } // if

    return true;
}

bool my::PlayerJumpAttackSetComponent::Release(void) {
    super::Release();
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
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionJumpAttackSetState);
    } // if
    return true;
}

bool my::PlayerJumpAttackSetComponent::End(void) {
    super::End();
    return true;
}