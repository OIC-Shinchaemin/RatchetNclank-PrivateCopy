#include "PlayerThrowAttackComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"
#include "PlayerMoveComponent.h"
#include "PlayerWeaponComponent.h"


void my::PlayerThrowAttackComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::PlayerThrowAttackComponent::PlayerThrowAttackComponent(int priority) :
    super(priority),
    _state_com(),
    _motion_com(),
    _motion_state_com(),
    _weapon_com() {
}

my::PlayerThrowAttackComponent::PlayerThrowAttackComponent(const PlayerThrowAttackComponent& obj) :
    super(obj),
    _state_com(),
    _motion_com(),
    _motion_state_com(),
    _weapon_com() {
}

my::PlayerThrowAttackComponent::~PlayerThrowAttackComponent() {
}

std::string my::PlayerThrowAttackComponent::GetType(void) const {
    return "PlayerThrowAttackComponent";
}

std::string_view my::PlayerThrowAttackComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackState;
}

bool my::PlayerThrowAttackComponent::Initialize(void) {
    super::Initialize();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    _weapon_com = super::GetOwner()->GetComponent<my::PlayerWeaponComponent>();
    return true;
}

bool my::PlayerThrowAttackComponent::Update(float delta_time) {
    auto motion_com = _motion_com.lock();
    if (motion_com->IsEndMotion()) {
        this->ChageState(state::PlayerActionStateType::kPlayerActionThrowAttackEndState);
    } // if
    return true;
}

bool my::PlayerThrowAttackComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerThrowAttackComponent::Clone(void) {
    return std::make_shared<my::PlayerThrowAttackComponent>(*this);
}

bool my::PlayerThrowAttackComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionThrowAttackState);
    } // if
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Activate();
    } // if
    return true;
}

bool my::PlayerThrowAttackComponent::End(void) {
    super::End();
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Inactivate();
    } // if
    return true;
}