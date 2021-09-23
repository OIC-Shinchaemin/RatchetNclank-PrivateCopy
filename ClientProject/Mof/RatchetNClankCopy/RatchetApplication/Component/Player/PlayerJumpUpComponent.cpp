#include "PlayerJumpUpComponent.h"

#include "PlayerMoveComponent.h"


void ratchet::component::player::action::PlayerJumpUpComponent::InputJumpVelocity(float speed) {
    auto velocity_com = super::GetVelocityComponent();

    auto v = velocity_com->GetVelocity();
    v.y = speed;
    velocity_com->SetVelocity(v);
}

ratchet::component::player::action::PlayerJumpUpComponent::PlayerJumpUpComponent(int priority) :
    super(priority),
    _jump_speed(0.0f),
    _jump_decrase(0.4f),
    _move_speed(2.4f),
    _angular_speed(3.3f),
    _gravity_down(1.8),
    _move_com(),
    _force_move_radian_angle() {
}

ratchet::component::player::action::PlayerJumpUpComponent::PlayerJumpUpComponent(const PlayerJumpUpComponent& obj) :
    super(obj),
    _jump_speed(0.0f),
    _jump_decrase(obj._jump_decrase),
    _move_speed(obj._move_speed),
    _angular_speed(obj._angular_speed),
    _gravity_down(obj._gravity_down),
    _move_com(),
    _force_move_radian_angle() {
}

ratchet::component::player::action::PlayerJumpUpComponent::~PlayerJumpUpComponent() {
}

std::string ratchet::component::player::action::PlayerJumpUpComponent::GetType(void) const {
    return "PlayerJumpUpComponent";
}

std::string_view ratchet::component::player::action::PlayerJumpUpComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpUpState;
}

void ratchet::component::player::action::PlayerJumpUpComponent::SetMoveSpeed(float scalar) {
    this->_move_speed = scalar;
}

void ratchet::component::player::action::PlayerJumpUpComponent::SetAngularSpeed(float scalar) {
    this->_angular_speed = scalar;
}

void ratchet::component::player::action::PlayerJumpUpComponent::SetJumpSpeed(float scalar) {
    this->_jump_speed = scalar;
}

void ratchet::component::player::action::PlayerJumpUpComponent::SetGravityDown(float scalar) {
    this->_gravity_down = scalar;
}

bool ratchet::component::player::action::PlayerJumpUpComponent::Initialize(void) {
    super::Initialize();
    _move_com = super::GetOwner()->GetComponent<ratchet::component::ActionComponent>()->GetComponent<ratchet::component::player::action::PlayerMoveComponent>();
    return true;
}

bool ratchet::component::player::action::PlayerJumpUpComponent::Input(void) {
    if (::g_pInput->IsKeyPush(MOFKEY_J) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_A)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionDoubleJumpState);
    } // if
    else if (::g_pInput->IsKeyPush(MOFKEY_N) ||
             ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpAttackSetState);
    } // else if

    auto move_com = _move_com.lock();
    auto& [in, move_angle, move_flag] = _input_info;
    // flag
    move_flag = move_com->AquireInputData(in, move_angle);
    if (move_flag) {
        in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
    } // if
    return true;
}

bool ratchet::component::player::action::PlayerJumpUpComponent::Update(float delta_time) {
    auto move_com = _move_com.lock();

    if (0.0f < std::abs(_jump_speed)) {
        this->InputJumpVelocity(_jump_speed);
    } // if

    auto& [in, move_angle, move_flag] = _input_info;
    // flag
    if (move_flag) {
        if (_force_move_radian_angle.has_value()) {
            move_com->Move(_move_speed, _angular_speed, _force_move_radian_angle.value());
        } // if
        else {
            move_com->Move(_move_speed, _angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
        } //else
    } // if

    _jump_speed -= _jump_decrase;
    if (_jump_speed < 0.0f) {
        _jump_speed = 0.0f;
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpDownState);
    } // if
    return true;
}

bool ratchet::component::player::action::PlayerJumpUpComponent::Release(void) {
    super::Release();
    _move_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerJumpUpComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerJumpUpComponent>(*this);
}

bool ratchet::component::player::action::PlayerJumpUpComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionJumpUpState);

    auto velocity_com = super::GetVelocityComponent();
    velocity_com->SetGravity(_gravity_down);

    super::GetCameraComponent()->SetFollowCameraPrevPositionUpdateFlag(true);
    return true;
}

bool ratchet::component::player::action::PlayerJumpUpComponent::End(void) {
    super::End();

    super::GetCameraComponent()->SetFollowCameraPrevPositionUpdateFlag(false);
    return true;
}