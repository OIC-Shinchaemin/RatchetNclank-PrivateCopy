#include "PlayerMeleeAttackThreeComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerAction/PlayerActionStateDefine.h"
#include "../../State/PlayerMotion/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"
#include "PlayerMoveComponent.h"


void my::PlayerMeleeAttackThreeComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::PlayerMeleeAttackThreeComponent::PlayerMeleeAttackThreeComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com(),
    _move_com() {
}

my::PlayerMeleeAttackThreeComponent::PlayerMeleeAttackThreeComponent(const PlayerMeleeAttackThreeComponent& obj) :
    super(obj._priority),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com(),
    _move_com() {
}

my::PlayerMeleeAttackThreeComponent::~PlayerMeleeAttackThreeComponent() {
}

std::string my::PlayerMeleeAttackThreeComponent::GetType(void) const {
    return "PlayerMeleeAttackThreeComponent";
}

bool my::PlayerMeleeAttackThreeComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    _move_com = super::GetOwner()->GetComponent<my::PlayerMoveComponent>();
    return true;
}

bool my::PlayerMeleeAttackThreeComponent::Update(float delta_time) {
    puts("PlayerMeleeAttackThreeComponent");
    auto state_com = _state_com.lock();
    auto motion_com = _motion_com.lock();
    auto motion_state_com = _motion_state_com.lock();

    if (motion_com->IsEndMotion()) {
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionMeleeAttackThreeEndState);
    } // if
    return true;
}

bool my::PlayerMeleeAttackThreeComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerMeleeAttackThreeComponent::Clone(void) {
    return std::make_shared<my::PlayerMeleeAttackThreeComponent>(*this);
}

bool my::PlayerMeleeAttackThreeComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackThreeState);
    } // if

    if (auto move_com = _move_com.lock()) {
        Mof::CVector2 in; float move_angle;
        float move_speed = 10.0f; float angular_speed = 0.0f; float ideal_angle = super::GetOwner()->GetRotate().y;
        if (move_com->AquireInputData(in, move_angle)) {
            in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
            angular_speed = 15.0f; ideal_angle = std::atan2(-in.y, in.x) - math::kHalfPi;
        } // if
        move_com->Move(move_speed, angular_speed, ideal_angle);
    } // if

    return true;
}