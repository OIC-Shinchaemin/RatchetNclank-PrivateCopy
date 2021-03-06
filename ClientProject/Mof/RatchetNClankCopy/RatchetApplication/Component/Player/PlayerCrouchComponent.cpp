#include "PlayerCrouchComponent.h"

#include "../CameraComponent.h"
#include "PlayerMoveComponent.h"
#include "PlayerCartwheelJumpComponent.h"


ratchet::component::player::action::PlayerCrouchComponent::PlayerCrouchComponent(int priority) :
    super(priority),
    _angular_speed(),
    _ideal_angle(),
    _input_info(),
    _move_com(),
    _reception_timer(),
    _reception_time(0.6f) {
}

ratchet::component::player::action::PlayerCrouchComponent::PlayerCrouchComponent(const PlayerCrouchComponent& obj) :
    super(obj),
    _angular_speed(0.4f),
    _ideal_angle(),
    _input_info(),
    _move_com(),
    _reception_timer(),
    _reception_time(0.6f) {
}

ratchet::component::player::action::PlayerCrouchComponent::~PlayerCrouchComponent() {
}

void ratchet::component::player::action::PlayerCrouchComponent::SetAngularSpeed(float speed) {
    this->_angular_speed = speed;
}

void ratchet::component::player::action::PlayerCrouchComponent::SetIdealAngle(float radian) {
    this->_ideal_angle = radian;
}

std::string ratchet::component::player::action::PlayerCrouchComponent::GetType(void) const {
    return "PlayerCrouchComponent";
}

std::string_view ratchet::component::player::action::PlayerCrouchComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionCrouchState;
}

bool ratchet::component::player::action::PlayerCrouchComponent::Initialize(void) {
    super::Initialize();
    _move_com = super::GetOwner()->GetComponent<ratchet::component::ActionComponent>()->GetComponent<ratchet::component::player::action::PlayerMoveComponent>();
    return true;
}

bool ratchet::component::player::action::PlayerCrouchComponent::Input(void) {
    using Type = state::PlayerActionStateType;
    if (::g_pInput->IsKeyPull(MOFKEY_U) || ::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_R_BTN)) {
        super::ChangeActionState(Type::kPlayerActionIdleState);
    } // if
    else if (::g_pInput->IsKeyPush(MOFKEY_Z) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        super::ChangeActionState(Type::kPlayerActionThrowAttackSetState);
    } // else if


    if (auto move_com = super::GetOwner()->GetComponent<ratchet::component::ActionComponent>()->GetComponent<ratchet::component::player::action::PlayerMoveComponent>()) {
        auto camera_com = super::GetOwner()->GetComponent<ratchet::component::CameraComponent>();

        if (::g_pInput->IsKeyPush(MOFKEY_C) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_A)) {
            _reception_timer.Initialize(_reception_time, false);
        } // if

        Mof::CVector2 in; float move_angle;
        if (move_com->AquireInputData(in, move_angle)) {
            if (_reception_timer() < _reception_time) {
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
                float distance_threshold = 0.6f;
                if (distance_threshold < distance) {
                    move_com->AquireInputData(in, move_angle);
                    move_angle += math::kHalfPi + camera_angle_y;

                    MOF_NORMALIZE_RADIANANGLE(move_angle);
                    super::GetOwner()->GetComponent<ratchet::component::ActionComponent>()->GetComponent<ratchet::component::player::action::PlayerCartwheelJumpComponent>()->SetMoveAngle(move_angle);
                    super::ChangeActionState(Type::kPlayerActionCartwheelJumpState);
                } // if
            } // if
        } // if
    } // if

    auto move_com = _move_com.lock();
    auto& [in, move_angle, move_flag] = _input_info;
    move_flag = move_com->AquireInputData(in, move_angle);

    if (move_flag) {
        in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
    } // if

    return true;
}

bool ratchet::component::player::action::PlayerCrouchComponent::Update(float delta_time) {
    _reception_timer.Tick(delta_time);

    auto move_com = _move_com.lock();
    auto& [in, move_angle, move_flag] = _input_info;
    if (move_flag) {
        move_com->Move(0.0f, _angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
    } // if
    return true;
}

bool ratchet::component::player::action::PlayerCrouchComponent::Release(void) {
    super::Release();
    _move_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerCrouchComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerCrouchComponent>(*this);
}

bool ratchet::component::player::action::PlayerCrouchComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionCrouchState);
    return true;
}