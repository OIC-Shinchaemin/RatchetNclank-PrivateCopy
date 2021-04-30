#include "PlayerJumpUpComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerAction/PlayerActionStateDefine.h"
#include "PlayerStateComponent.h"
#include "../VelocityComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "PlayerMoveComponent.h"


void my::PlayerJumpUpComponent::InputJumpVelocity(float speed) {
    if (auto velocity_com = _velocity_com.lock()) {
        auto v = velocity_com->GetVelocity();
        v.y = speed;
        velocity_com->SetVelocity(v);
    } // if
}

my::PlayerJumpUpComponent::PlayerJumpUpComponent(int priority) :
    super(priority),
    _jump_speed_max(20.0f),
    _jump_speed(_jump_speed_max),
    _jump_decrase(1.0f),
    _state_com(),
    _velocity_com(),
    _motion_state_com(),
    _move_com() {
}

my::PlayerJumpUpComponent::PlayerJumpUpComponent(const PlayerJumpUpComponent& obj) :
    super(obj._priority),
    _jump_speed_max(obj._jump_speed_max),
    _jump_speed(obj._jump_speed),
    _jump_decrase(obj._jump_decrase),
    _state_com(),
    _velocity_com(),
    _motion_state_com(),
    _move_com() {

}

my::PlayerJumpUpComponent::~PlayerJumpUpComponent() {
}

std::string my::PlayerJumpUpComponent::GetType(void) const {
    return "PlayerJumpUpComponent";
}

bool my::PlayerJumpUpComponent::Initialize(void) {
    super::Initialize();

    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    _move_com = super::GetOwner()->GetComponent<my::PlayerMoveComponent>();
    return true;
}

bool my::PlayerJumpUpComponent::Update(float delta_time) {
    puts("PlayerJumpUpComponent");
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
        velocity_com->SetGravity(4.8f);
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionJumpDownState);
    } // if
    return true;
}

bool my::PlayerJumpUpComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerJumpUpComponent::Clone(void) {
    return std::make_shared<my::PlayerJumpUpComponent>(*this);
}

bool my::PlayerJumpUpComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("PlayerMotionJumpUpState");
    } // if
    if (auto velocity_com = _velocity_com.lock()) {
        velocity_com->SetGravity(3.8f);
    } // if
    _jump_speed = _jump_speed_max;
    return true;
}