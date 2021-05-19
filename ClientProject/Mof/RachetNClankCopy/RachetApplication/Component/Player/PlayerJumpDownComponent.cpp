#include "PlayerJumpDownComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"
#include "PlayerStateComponent.h"
#include "../VelocityComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "PlayerMoveComponent.h"


my::PlayerJumpDownComponent::PlayerJumpDownComponent(int priority) :
    super(priority),
    _jump_speed_max(20.0f),
    _jump_speed(_jump_speed_max),
    _jump_decrase(1.0f),
    _state_com(),
    _velocity_com(),
    _motion_state_com(),
    _move_com() {
}

my::PlayerJumpDownComponent::PlayerJumpDownComponent(const PlayerJumpDownComponent& obj) :
    super(obj),
    _jump_speed_max(obj._jump_speed_max),
    _jump_speed(obj._jump_speed),
    _jump_decrase(obj._jump_decrase),
    _state_com(),
    _velocity_com(),
    _motion_state_com(),
    _move_com() {
}

my::PlayerJumpDownComponent::~PlayerJumpDownComponent() {
}

std::string my::PlayerJumpDownComponent::GetType(void) const {
    return "PlayerJumpDownComponent";
}

std::string_view my::PlayerJumpDownComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpDownState;
}

bool my::PlayerJumpDownComponent::Initialize(void) {
    super::Initialize();

    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    _move_com = super::GetOwner()->GetComponent<my::PlayerMoveComponent>();
    return true;
}

bool my::PlayerJumpDownComponent::Update(float delta_time) {
    auto move_com = _move_com.lock();
    auto state_com = _state_com.lock();

    Mof::CVector2 in;
    float move_angle;

    // flag
    if (move_com->AquireInputData(in, move_angle)) {
        float move_speed = 1.7f; float angular_speed = 3.3f;
        in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
        move_com->Move(move_speed, angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
    } // if

    if (::g_pInput->IsKeyPush(MOFKEY_Z) ||
             ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionJumpAttackSetState);
    } // if

    return true;
}

bool my::PlayerJumpDownComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerJumpDownComponent::Clone(void) {
    return std::make_shared<my::PlayerJumpDownComponent>(*this);
}

bool my::PlayerJumpDownComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionJumpDownState);
    } // if
    if (auto velocity_com = _velocity_com.lock()) {
        velocity_com->SetGravity(2.0f);
    } // if

    return true;
}