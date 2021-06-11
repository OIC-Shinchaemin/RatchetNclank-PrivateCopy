#include "PlayerJumpUpComponent.h"

#include "PlayerMoveComponent.h"


void ratchet::PlayerJumpUpComponent::InputJumpVelocity(float speed) {
    auto velocity_com = super::GetVelocityComponent();

    auto v = velocity_com->GetVelocity();
    v.y = speed;
    velocity_com->SetVelocity(v);
}

ratchet::PlayerJumpUpComponent::PlayerJumpUpComponent(int priority) :
    super(priority),
    _jump_speed(0.0f),
    _jump_decrase(0.4f),
    _move_com() {
}

ratchet::PlayerJumpUpComponent::PlayerJumpUpComponent(const PlayerJumpUpComponent& obj) :
    super(obj),
    _jump_speed(0.0f),
    _jump_decrase(obj._jump_decrase),
    _move_com() {
}

ratchet::PlayerJumpUpComponent::~PlayerJumpUpComponent() {
}

std::string ratchet::PlayerJumpUpComponent::GetType(void) const {
    return "PlayerJumpUpComponent";
}

std::string_view ratchet::PlayerJumpUpComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpUpState;
}

void ratchet::PlayerJumpUpComponent::SetJumpSpeed(float speed) {
    this->_jump_speed = speed;
}

bool ratchet::PlayerJumpUpComponent::Initialize(void) {
    super::Initialize();
    _move_com = super::GetOwner()->GetComponent<ratchet::ActionComponent>()->GetComponent<ratchet::PlayerMoveComponent>();
    return true;
}

bool ratchet::PlayerJumpUpComponent::Input(void) {
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
        //float move_speed = 2.4f; float angular_speed = 3.3f;
        //move_com->Move(move_speed, angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
    } // if


    return true;
}

bool ratchet::PlayerJumpUpComponent::Update(float delta_time) {
    auto move_com = _move_com.lock();

    if (0.0f < std::abs(_jump_speed)) {
        this->InputJumpVelocity(_jump_speed);
    } // if



//    Mof::CVector2 in;
//    float move_angle;

    auto& [in, move_angle, move_flag] = _input_info;
    // flag
    if (move_flag) {
        float move_speed = 2.4f; float angular_speed = 3.3f;
        move_com->Move(move_speed, angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
    } // if

    /// 

    _jump_speed -= _jump_decrase;
    if (_jump_speed < 0.0f) {
        _jump_speed = 0.0f;
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpDownState);
    } // if
    return true;
}

bool ratchet::PlayerJumpUpComponent::Release(void) {
    super::Release();
    _move_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerJumpUpComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerJumpUpComponent>(*this);
}

bool ratchet::PlayerJumpUpComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionJumpUpState);

    auto velocity_com = super::GetVelocityComponent();
    velocity_com->SetGravity(1.8f);
    return true;
}