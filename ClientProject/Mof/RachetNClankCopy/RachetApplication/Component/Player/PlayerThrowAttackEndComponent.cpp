#include "PlayerThrowAttackEndComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"
#include "PlayerMoveComponent.h"
#include "PlayerWeaponComponent.h"


void my::PlayerThrowAttackEndComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::PlayerThrowAttackEndComponent::PlayerThrowAttackEndComponent(int priority) :
    super(priority), 
    _motion_com(),
    _motion_state_com(),
    _weapon_com() {
}

my::PlayerThrowAttackEndComponent::PlayerThrowAttackEndComponent(const PlayerThrowAttackEndComponent& obj) :
    super(obj), 
    _motion_com(),
    _motion_state_com(),
    _weapon_com() {
}

my::PlayerThrowAttackEndComponent::~PlayerThrowAttackEndComponent() {
}

std::string my::PlayerThrowAttackEndComponent::GetType(void) const {
    return "PlayerThrowAttackEndComponent";
}

std::string_view my::PlayerThrowAttackEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionThrowAttackEndState;
}

bool my::PlayerThrowAttackEndComponent::Initialize(void) {
    super::Initialize();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    _weapon_com = super::GetOwner()->GetComponent<my::PlayerWeaponComponent>();
    return true;
}

bool my::PlayerThrowAttackEndComponent::Update(float delta_time) {
    auto motion_com = _motion_com.lock();
    if (motion_com->IsEndMotion()) {
        this->ChageState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

bool my::PlayerThrowAttackEndComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerThrowAttackEndComponent::Clone(void) {
    return std::make_shared<my::PlayerThrowAttackEndComponent>(*this);
}

bool my::PlayerThrowAttackEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionThrowAttackEndState);
    } // if
    return true;
}

bool my::PlayerThrowAttackEndComponent::End(void) {
    super::End();
    return true;
}