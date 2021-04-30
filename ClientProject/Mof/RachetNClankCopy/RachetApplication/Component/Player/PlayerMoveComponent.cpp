#include "PlayerMoveComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerAction/PlayerActionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../CameraComponent.h"


void my::PlayerMoveComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

void my::PlayerMoveComponent::InputMoveVelocity(float speed) {
    if (auto velocity_com = _velocity_com.lock()) {
        auto accele = Mof::CVector3(0.0f, 0.0f, -speed);
        auto rotate = super::GetOwner()->GetRotate();
        accele.RotateAround(Mof::CVector3(), rotate);

        velocity_com->AddVelocityForce(accele);
    } // if
}

void my::PlayerMoveComponent::InputMoveAngularVelocity(float angle, float speed) {
    if (auto velocity_com = _velocity_com.lock()) {

        auto view_front = _camera_com.lock()->GetViewFront();
        float camera_angle_y = std::atan2(-view_front.z, view_front.x) + math::kHalfPi;
        float angle_y = angle + camera_angle_y;
        if (math::kTwoPi <= angle_y) {
            angle_y -= math::kTwoPi;
        } // if
        else if (angle_y <= 0.0f) {
            angle_y += math::kTwoPi;
        } // else if

        auto rotate = super::GetOwner()->GetRotate();
        // ç∑ï™äpìx
        angle_y -= rotate.y;
        if (math::kPi < angle_y) {
            angle_y -= math::kTwoPi;
        } // if
        else if (angle_y < -math::kPi) {
            angle_y += math::kTwoPi;
        } // else if

        auto accele = Mof::CVector3(0.0f, angle_y * speed, 0.0f);
        velocity_com->AddAngularVelocityForce(accele);
    } // if
}

my::PlayerMoveComponent::PlayerMoveComponent(int priority) :
    super(priority),
    _move_speed(1.8f),
    _angular_speed(3.5f),
    _ideal_angle(0.0f),
    _velocity_com(),
    _motion_state_com() {
}

my::PlayerMoveComponent::PlayerMoveComponent(const PlayerMoveComponent& obj) :
    super(obj._priority),
    _move_speed(obj._move_speed),
    _angular_speed(obj._angular_speed),
    _ideal_angle(obj._ideal_angle),
    _velocity_com(),
    _motion_state_com(),
    _camera_com() {
}

my::PlayerMoveComponent::~PlayerMoveComponent() {
}

void my::PlayerMoveComponent::SetMoveSpeed(float speed) {
    this->_move_speed = speed;
}

void my::PlayerMoveComponent::SetAngularSpeed(float speed) {
    this->_angular_speed = speed;
}

void my::PlayerMoveComponent::SetIdealAngle(float radian) {
    this->_ideal_angle = radian;
}

float my::PlayerMoveComponent::GetDefaultMoveSpeed(void) const {
    return 1.3f;
}

float my::PlayerMoveComponent::GetMoveSpeed(void) const {
    return this->_move_speed;
}

std::string my::PlayerMoveComponent::GetType(void) const {
    return "PlayerMoveComponent";
}

bool my::PlayerMoveComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    _camera_com = super::GetOwner()->GetComponent<my::CameraComponent>();

    return true;
}

bool my::PlayerMoveComponent::Update(float delta_time) {
    Mof::CVector2 in;
    float move_angle;
    bool jump_flag = false;

    // flag
    bool action = this->AquireInputData(in , move_angle);
    if (::g_pInput->IsKeyPush(MOFKEY_X) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_B)) {
        jump_flag = true;
    } // if

    // transition
    if (jump_flag) {
        this->ChageState(state::PlayerActionStateType::kPlayerActionJumpSetState);
    } // if
    if (action) {
        in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
        this->Move(_move_speed, _angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
    } // if
    else {
        this->ChageState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // else
    return true;
}

bool my::PlayerMoveComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerMoveComponent::Clone(void) {
    return std::make_shared<my::PlayerMoveComponent>(*this);
}

bool my::PlayerMoveComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("PlayerMotionMoveState");
    } // if
    return true;
}

bool my::PlayerMoveComponent::Move(float move_speed, float angular_speed, float ideal_angle) {
    this->InputMoveAngularVelocity(ideal_angle, angular_speed);
    this->InputMoveVelocity(move_speed);
    return true;
}

bool my::PlayerMoveComponent::AquireInputData(Mof::CVector2& stick, float& move_angle) {
    move_angle = 0.0f;

    float h = ::g_pGamepad->GetStickHorizontal(); float v = ::g_pGamepad->GetStickVertical();
    stick = Mof::CVector2(h, v);

    bool action = false; bool left = false; bool right = false;
    float threshold = 0.5f;

    // gamepad
    if (stick.Length() > threshold) {
        action = true;
    } // if
    // keyboard
    else {
        stick = Mof::CVector2(1.0f, 0.0f);

        if (::g_pInput->IsKeyHold(MOFKEY_A)) {
            action = true;
            left = true;
            move_angle = 180.0f;
        } // if
        else if (::g_pInput->IsKeyHold(MOFKEY_D)) {
            action = true;
            right = true;
            move_angle = 0.0f;
        } // else if
        if (::g_pInput->IsKeyHold(MOFKEY_W)) {
            action = true;
            move_angle = 90.0f;
            if (right) {
                move_angle -= 45.0f;
            } // if
            else if (left) {
                move_angle += 45.0f;
            } // else if
        } // else if
        else if (::g_pInput->IsKeyHold(MOFKEY_S)) {
            action = true;
            move_angle = 270.0f;
            if (right) {
                move_angle += 45.0f;
            } // if
            else if (left) {
                move_angle -= 45.0f;
            } // else if
        } // else if
    } // else
    return action;
}