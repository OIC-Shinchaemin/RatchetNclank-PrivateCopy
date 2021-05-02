#include "PlayerDoubleJumpComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerAction/PlayerActionStateDefine.h"
#include "../../State/PlayerMotion/PlayerMotionStateDefine.h"
#include "PlayerStateComponent.h"
#include "../VelocityComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "PlayerMoveComponent.h"


void my::PlayerDoubleJumpComponent::InputJumpVelocity(float speed) {
    if (auto velocity_com = _velocity_com.lock()) {
        auto v = velocity_com->GetVelocity();
        v.y = speed;
        velocity_com->SetVelocity(v);
    } // if
}

my::PlayerDoubleJumpComponent::PlayerDoubleJumpComponent(int priority) :
    super(priority),
    _jump_speed(0.0f),
    _jump_decrase(0.4f),
    _state_com(),
    _velocity_com(),
    _motion_state_com(),
    _move_com() {
}

my::PlayerDoubleJumpComponent::PlayerDoubleJumpComponent(const PlayerDoubleJumpComponent& obj) :
    super(obj._priority),
    _jump_speed(0.0f),
    _jump_decrase(obj._jump_decrase),
    _state_com(),
    _velocity_com(),
    _motion_state_com(),
    _move_com() {

}

my::PlayerDoubleJumpComponent::~PlayerDoubleJumpComponent() {
}

std::string my::PlayerDoubleJumpComponent::GetType(void) const {
    return "PlayerDoubleJumpComponent";
}

void my::PlayerDoubleJumpComponent::SetJumpSpeed(float speed) {
    this->_jump_speed = speed;
}

bool my::PlayerDoubleJumpComponent::Initialize(void) {
    super::Initialize();

    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    _move_com = super::GetOwner()->GetComponent<my::PlayerMoveComponent>();
    return true;
}

bool my::PlayerDoubleJumpComponent::Update(float delta_time) {
    auto state_com = _state_com.lock();
    auto motion_com = _motion_com.lock();
    auto motion_state_com = _motion_state_com.lock();
    auto velocity_com = _velocity_com.lock();
    auto move_com = _move_com.lock();

    if (0.0f < std::abs(_jump_speed)) {
        this->InputJumpVelocity(_jump_speed);
    } // if
    Mof::CVector2 in;
    float move_angle;
    bool jump_flag = false;

    // flag
    if (move_com->AquireInputData(in, move_angle)) {
        float move_speed = 1.7f; float angular_speed = 3.3f;
        in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
        move_com->Move(move_speed, angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
    } // if

    _jump_speed -= _jump_decrase;
    if (_jump_speed < 0.0f) {
        _jump_speed = 0.0f;
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionJumpDownState);
    } // if
    return true;
}

bool my::PlayerDoubleJumpComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerDoubleJumpComponent::Clone(void) {
    return std::make_shared<my::PlayerDoubleJumpComponent>(*this);
}

bool my::PlayerDoubleJumpComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionDoubleJumpState);
    } // if
    if (auto velocity_com = _velocity_com.lock()) {
        velocity_com->SetGravity(1.8f);
    } // if

    _jump_speed = 10.0f;
    return true;
}