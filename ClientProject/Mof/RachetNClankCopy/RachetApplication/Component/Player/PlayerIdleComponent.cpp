#include "PlayerIdleComponent.h"

#include "../../Gamepad.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"


/*
void my::PlayerIdleComponent::InputMoveAngularVelocity(float angle, float speed) {
    if (auto velocity_com = _velocity_com.lock()) {

        float angle_y = angle;
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
*/

void my::PlayerIdleComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::PlayerIdleComponent::PlayerIdleComponent(int priority) :
    super(priority),
    _angular_speed(0.0f),
    _ideal_angle(0.0f),
    _velocity_com(),
    _state_com(),
    _motion_state_com() {
}

my::PlayerIdleComponent::PlayerIdleComponent(const PlayerIdleComponent& obj) :
    super(obj._priority),
    _angular_speed(obj._angular_speed),
    _ideal_angle(obj._ideal_angle),
    _velocity_com(),
    _state_com(),
    _motion_state_com() {
}

my::PlayerIdleComponent::~PlayerIdleComponent() {
}

void my::PlayerIdleComponent::SetAngularSpeed(float speed) {
    this->_angular_speed = speed;
}

void my::PlayerIdleComponent::SetIdealAngle(float radian) {
    this->_ideal_angle = radian;
}

std::string my::PlayerIdleComponent::GetType(void) const {
    return "PlayerIdleComponent";
}

bool my::PlayerIdleComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::PlayerIdleComponent::Update(float delta_time) {
    puts("PlayerIdleComponent");
    float h = ::g_pGamepad->GetStickHorizontal(); float v = ::g_pGamepad->GetStickVertical();
    float threshold = 0.5f;
    auto stick = Mof::CVector2(h, v);

    if (::g_pInput->IsKeyHold(MOFKEY_W) ||
        ::g_pInput->IsKeyHold(MOFKEY_A) ||
        ::g_pInput->IsKeyHold(MOFKEY_S) ||
        ::g_pInput->IsKeyHold(MOFKEY_D) ||
        stick.Length() > threshold) {
        this->ChageState("PlayerActionMoveState");
    } // if
    else if (::g_pInput->IsKeyPush(MOFKEY_X) || 
             ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_B)) {
        this->ChageState("PlayerActionJumpState");
    } // else if
    return true;
}

bool my::PlayerIdleComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerIdleComponent::Clone(void) {
    return std::make_shared<my::PlayerIdleComponent>(*this);
}

bool my::PlayerIdleComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("PlayerMotionIdleState");
    } // if
    return true;
}