#include "PlayerCrouchComponent.h"

#include "../CameraComponent.h"
#include "PlayerMoveComponent.h"
#include "PlayerCartwheelJumpComponent.h"


my::PlayerCrouchComponent::PlayerCrouchComponent(int priority) :
    super(priority),
    _angular_speed(),
    _ideal_angle(),
    _move_com() {
}

my::PlayerCrouchComponent::PlayerCrouchComponent(const PlayerCrouchComponent& obj) :
    super(obj),
    _angular_speed(0.4f),
    _ideal_angle(),
    _move_com() {
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
    _move_com = super::GetOwner()->GetComponent<my::ActionComponent>()->GetComponent<my::PlayerMoveComponent>();
    return true;
}

bool my::PlayerCrouchComponent::Update(float delta_time) {
    using Type = state::PlayerActionStateType;
    if (::g_pInput->IsKeyPull(MOFKEY_U) || ::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_R_BTN)) {
        super::ChangeActionState(Type::kPlayerActionIdleState);
    } // if
    else if (::g_pInput->IsKeyPush(MOFKEY_Z) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        super::ChangeActionState(Type::kPlayerActionThrowAttackSetState);
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_C) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_A)) {
        if (auto move_com = super::GetOwner()->GetComponent<my::ActionComponent>()->GetComponent<my::PlayerMoveComponent>()) {
            auto camera_com = super::GetOwner()->GetComponent<my::CameraComponent>();

            Mof::CVector2 in; float move_angle;
            if (move_com->AquireInputData(in, move_angle)) {
                in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
                auto view_front = camera_com->GetViewFront();
                float camera_angle_y = std::atan2(-view_front.z, view_front.x);
                float move_angle = std::atan2(-in.y, in.x);
                move_angle += camera_angle_y;
                MOF_NORMALIZE_RADIANANGLE(move_angle);

                float owner_rotate_y = super::GetOwner()->GetRotate().y;
                auto owner_circle_position = Mof::CVector2(std::cosf(owner_rotate_y), std::sinf(owner_rotate_y));
                auto input_circle_position = Mof::CVector2(std::cosf(move_angle), std::sinf(move_angle));
                float distance = Mof::CVector2Utilities::Distance(owner_circle_position, input_circle_position);
                float distance_threshold = 1.3f;
                if (distance_threshold < distance) {
                    move_com->AquireInputData(in, move_angle);
                    move_angle += math::kHalfPi + camera_angle_y;
                    
                    MOF_NORMALIZE_RADIANANGLE(move_angle);
                    super::GetOwner()->GetComponent<my::ActionComponent>()->GetComponent<my::PlayerCartwheelJumpComponent>()->SetMoveAngle(move_angle);
                    super::ChangeActionState(Type::kPlayerActionCartwheelJumpState);
                } // if
            } // if
        } // if

    } // else if




    if (auto move_com = _move_com.lock()) {
        Mof::CVector2 in;
        if (move_com->AquireInputData(in, _ideal_angle)) {
            in = math::Rotate(in.x, in.y, math::ToRadian(_ideal_angle));
            move_com->Move(0.0f, _angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
        } // if
    } // if
    return true;
    return true;
}

bool my::PlayerCrouchComponent::Release(void) {
    super::Release();
    _move_com.reset();
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