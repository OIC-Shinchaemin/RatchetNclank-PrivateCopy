#include "PlayerThrowAttackSetComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"
#include "PlayerMoveComponent.h"
#include "PlayerWeaponComponent.h"



void my::PlayerThrowAttackSetComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::PlayerThrowAttackSetComponent::PlayerThrowAttackSetComponent(int priority) :
    super(priority),
    _state_com(),
    _motion_com(),
    _motion_state_com(),
    _weapon_com() {
}

my::PlayerThrowAttackSetComponent::PlayerThrowAttackSetComponent(const PlayerThrowAttackSetComponent& obj) :
    super(obj),
    _state_com(),
    _motion_com(),
    _motion_state_com(),
    _weapon_com() {
}

my::PlayerThrowAttackSetComponent::~PlayerThrowAttackSetComponent() {
}

std::string my::PlayerThrowAttackSetComponent::GetType(void) const {
    return "PlayerThrowAttackSetComponent";
}

std::string_view my::PlayerThrowAttackSetComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackSetState;
}

bool my::PlayerThrowAttackSetComponent::Initialize(void) {
    super::Initialize();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    _weapon_com = super::GetOwner()->GetComponent<my::PlayerWeaponComponent>();
    return true;
}

bool my::PlayerThrowAttackSetComponent::Update(float delta_time) {
    auto motion_com = _motion_com.lock();

    if (motion_com->IsEndMotion()) {
        this->ChageState(state::PlayerActionStateType::kPlayerActionThrowAttackState);
    } // if
    return true;
}

bool my::PlayerThrowAttackSetComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerThrowAttackSetComponent::Clone(void) {
    return std::make_shared<my::PlayerThrowAttackSetComponent>(*this);
}

bool my::PlayerThrowAttackSetComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionThrowAttackSetState);
    } // if
    /*
    if (auto weapon_com = _weapon_com.lock()) {
        weapon_com->Activate();
    } // if
    */
    return true;
}

bool my::PlayerThrowAttackSetComponent::End(void) {
    super::End();
    return true;
}