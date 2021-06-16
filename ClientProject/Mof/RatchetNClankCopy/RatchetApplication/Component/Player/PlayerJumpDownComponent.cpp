#include "PlayerJumpDownComponent.h"

#include "PlayerMoveComponent.h"


ratchet::component::player::action::PlayerJumpDownComponent::PlayerJumpDownComponent(int priority) :
    super(priority),
    _jump_speed_max(20.0f),
    _jump_speed(_jump_speed_max),
    _jump_decrase(1.0f),
    _input_info(),
    _move_com() {
}

ratchet::component::player::action::PlayerJumpDownComponent::PlayerJumpDownComponent(const PlayerJumpDownComponent& obj) :
    super(obj),
    _jump_speed_max(obj._jump_speed_max),
    _jump_speed(obj._jump_speed),
    _jump_decrase(obj._jump_decrase),
    _input_info(),
    _move_com() {
}

ratchet::component::player::action::PlayerJumpDownComponent::~PlayerJumpDownComponent() {
}

std::string ratchet::component::player::action::PlayerJumpDownComponent::GetType(void) const {
    return "PlayerJumpDownComponent";
}

std::string_view ratchet::component::player::action::PlayerJumpDownComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpDownState;
}

bool ratchet::component::player::action::PlayerJumpDownComponent::Initialize(void) {
    super::Initialize();
    _move_com = super::GetOwner()->GetComponent<ratchet::component::ActionComponent>()->GetComponent<ratchet::component::player::action::PlayerMoveComponent>();
    return true;
}

bool ratchet::component::player::action::PlayerJumpDownComponent::Input(void) {
    auto move_com = _move_com.lock();
    auto& [in, move_angle, move_flag] = _input_info;
    move_flag = move_com->AquireInputData(in, move_angle);

    if (move_flag) {
        in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
    } // if

    return true;
}

bool ratchet::component::player::action::PlayerJumpDownComponent::Update(float delta_time) {
    auto move_com = _move_com.lock();

    //Mof::CVector2 in;
    //float move_angle;

    auto& [in, move_angle, move_flag] = _input_info;
    if (move_flag) {
        float move_speed = 1.7f; float angular_speed = 3.3f;
        //in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
        move_com->Move(move_speed, angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
    } // if



    if (::g_pInput->IsKeyPush(MOFKEY_Z) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpAttackSetState);
    } // if

    _input_info.Reset();
    return true;
}

bool ratchet::component::player::action::PlayerJumpDownComponent::Release(void) {
    super::Release();
    _move_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::player::action::PlayerJumpDownComponent::Clone(void) {
    return std::make_shared<ratchet::component::player::action::PlayerJumpDownComponent>(*this);
}

bool ratchet::component::player::action::PlayerJumpDownComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionJumpDownState);

    auto velocity_com = super::GetVelocityComponent();
    velocity_com->SetGravity(2.0f);
    return true;
}