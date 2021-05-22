#include "PlayerCrouchComponent.h"

#include "../CameraComponent.h"

/*
void my::PlayerCrouchComponent::InputMoveVelocity(float speed) {
    auto velocity_com = super::GetVelocityComponent();
    auto accele = Mof::CVector3(0.0f, 0.0f, -speed);
    auto rotate = super::GetOwner()->GetRotate();
    accele.RotateAround(Mof::CVector3(), rotate);
    velocity_com->AddVelocityForce(accele);
}

void my::PlayerCrouchComponent::InputMoveAngularVelocity(float angle, float speed) {
    auto velocity_com = super::GetVelocityComponent();

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
}
*/

my::PlayerCrouchComponent::PlayerCrouchComponent(int priority) :
    super(priority),
    _angular_speed(),
    _ideal_angle() ,
    _camera_com() {
}

my::PlayerCrouchComponent::PlayerCrouchComponent(const PlayerCrouchComponent& obj) :
    super(obj),
    _angular_speed(),
    _ideal_angle(),
    _camera_com() {
}

my::PlayerCrouchComponent::~PlayerCrouchComponent() {
}

void my::PlayerCrouchComponent::SetAngularSpeed(float speed) {
    this->_angular_speed = speed;
}

void my::PlayerCrouchComponent::SetIdealAngle(float radian) {
    this->_ideal_angle = radian;
}

std::string my::PlayerCrouchComponent::GetType(void) const {
    return "PlayerCrouchComponent";
}

std::string_view my::PlayerCrouchComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionCrouchState;
}

bool my::PlayerCrouchComponent::Initialize(void) {
    super::Initialize();

    _camera_com = super::GetOwner()->GetComponent<my::CameraComponent>();
    return true;
}

bool my::PlayerCrouchComponent::Update(float delta_time) {
    if (::g_pInput->IsKeyPull(MOFKEY_U) || ::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_R_BTN)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    else if (::g_pInput->IsKeyPush(MOFKEY_Z) ||
             (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X) && ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X))) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionThrowAttackSetState);
    } // else if

    return true;
}

bool my::PlayerCrouchComponent::Release(void) {
    super::Release();
    _camera_com.reset();
    return true;
}

std::shared_ptr<my::Component> my::PlayerCrouchComponent::Clone(void) {
    return std::make_shared<my::PlayerCrouchComponent>(*this);
}

bool my::PlayerCrouchComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionCrouchState);
    return true;
}
/*
bool my::PlayerCrouchComponent::Move(float move_speed, float angular_speed, float ideal_angle) {
    this->InputMoveAngularVelocity(ideal_angle, angular_speed);
    this->InputMoveVelocity(move_speed);
    return true;
}

bool my::PlayerCrouchComponent::AquireInputData(Mof::CVector2& stick, float& move_angle) {
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
*/