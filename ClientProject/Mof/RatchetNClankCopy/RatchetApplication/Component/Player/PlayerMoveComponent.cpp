#include "PlayerMoveComponent.h"

#include "../../Actor/Character/Player.h"
#include "PlayerComponent.h"
#include "../CameraComponent.h"


void ratchet::component::player::action::PlayerMoveComponent::InputMoveVelocity(float speed) {
    auto velocity_com = super::GetVelocityComponent();
    auto accele = Mof::CVector3(0.0f, 0.0f, -speed);
    auto rotate = super::GetOwner()->GetRotate();
    accele.RotateAround(Mof::CVector3(), rotate);
    velocity_com->AddVelocityForce(accele);
}

void ratchet::component::player::action::PlayerMoveComponent::InputMoveAngularVelocity(float angle, float speed) {
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

ratchet::component::player::action::PlayerMoveComponent::PlayerMoveComponent(int priority) :
    super(priority),
    _move_speed(2.5f),
    _angular_speed(3.5f),
    _ideal_angle(0.0f),
    _input_info() {
}

ratchet::component::player::action::PlayerMoveComponent::PlayerMoveComponent(const PlayerMoveComponent& obj) :
    super(obj),
    _move_speed(obj._move_speed),
    _angular_speed(obj._angular_speed),
    _ideal_angle(obj._ideal_angle),
    _input_info(),
    _camera_com() {
}

ratchet::component::player::action::PlayerMoveComponent::~PlayerMoveComponent() {
}

void ratchet::component::player::action::PlayerMoveComponent::SetMoveSpeed(float speed) {
    this->_move_speed = speed;
}

void ratchet::component::player::action::PlayerMoveComponent::SetAngularSpeed(float speed) {
    this->_angular_speed = speed;
}

void ratchet::component::player::action::PlayerMoveComponent::SetIdealAngle(float radian) {
    this->_ideal_angle = radian;
}

float ratchet::component::player::action::PlayerMoveComponent::GetDefaultMoveSpeed(void) const {
    return 1.3f;
}

float ratchet::component::player::action::PlayerMoveComponent::GetMoveSpeed(void) const {
    return this->_move_speed;
}

std::string ratchet::component::player::action::PlayerMoveComponent::GetType(void) const {
    return "PlayerMoveComponent";
}

std::string_view ratchet::component::player::action::PlayerMoveComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMoveState;
}

bool ratchet::component::player::action::PlayerMoveComponent::Initialize(void) {
    super::Initialize();

    _camera_com = super::GetOwner()->GetComponent<ratchet::component::CameraComponent>();
    _type_com = super::GetOwner()->GetComponent<ratchet::component::player::PlayerComponent>();
    return true;
}

bool ratchet::component::player::action::PlayerMoveComponent::Input(void) {
    // flag
    if (::g_pInput->IsKeyPush(MOFKEY_J) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_A)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpSetState);
    } // if
    else if (::g_pInput->IsKeyPush(MOFKEY_N) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMeleeAttackOneState);
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_M) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_B)) {
        auto owner = std::dynamic_pointer_cast<ratchet::actor::character::Player>(super::GetOwner());
        if (owner->GetCurrentMechanical()) {
            super::ChangeActionState(state::PlayerActionStateType::kPlayerActionShotAttackState);
        } // if
    } // else if


    auto& [in, move_angle, move_flag, jump_flag, attack_flag] = _input_info;
    move_flag = this->AquireInputData(in, move_angle);
    if (move_flag) {
        in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
    } // if
    else {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // else

    return false;
}

bool ratchet::component::player::action::PlayerMoveComponent::Update(float delta_time) {
    if (_input_info.move_flag) {
        this->Move(_move_speed, _angular_speed, std::atan2(-_input_info.in.y, _input_info.in.x) - math::kHalfPi);
    } // if
    else {
        //super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // else

    _input_info.Reset();
    return true;
}

bool ratchet::component::player::action::PlayerMoveComponent::Release(void) {
    super::Release();
    _camera_com.reset();
    _type_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerMoveComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerMoveComponent>(*this);
}

bool ratchet::component::player::action::PlayerMoveComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionMoveState);
    return true;
}

bool ratchet::component::player::action::PlayerMoveComponent::Move(float move_speed, float angular_speed, float ideal_angle) {
    this->InputMoveAngularVelocity(ideal_angle, angular_speed);
    this->InputMoveVelocity(move_speed);
    return true;
}

bool ratchet::component::player::action::PlayerMoveComponent::AquireInputData(Mof::CVector2& stick, float& move_angle) {
    move_angle = 0.0f;

    float h = ::g_pGamepad->GetStickHorizontal(); float v = ::g_pGamepad->GetStickVertical();
    stick = Mof::CVector2(h, v);

    bool action = false; bool left = false; bool right = false;
    float threshold = 0.5f;

    // gamepad
    if (stick.Length() > threshold) {
        move_angle = std::atan2(-stick.y, stick.x) - math::kHalfPi;
        return true;
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