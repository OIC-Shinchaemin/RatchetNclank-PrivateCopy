#include "PlayerJumpDownComponent.h"

#include "PlayerMoveComponent.h"


my::PlayerJumpDownComponent::PlayerJumpDownComponent(int priority) :
    super(priority),
    _jump_speed_max(20.0f),
    _jump_speed(_jump_speed_max),
    _jump_decrase(1.0f),
    _move_com() {
}

my::PlayerJumpDownComponent::PlayerJumpDownComponent(const PlayerJumpDownComponent& obj) :
    super(obj),
    _jump_speed_max(obj._jump_speed_max),
    _jump_speed(obj._jump_speed),
    _jump_decrase(obj._jump_decrase),
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
    _move_com = super::GetOwner()->GetComponent<my::ActionComponent>()->GetComponent<my::PlayerMoveComponent>();
    return true;
}

bool my::PlayerJumpDownComponent::Update(float delta_time) {
    auto move_com = _move_com.lock();

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
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpAttackSetState);
    } // if

    return true;
}

bool my::PlayerJumpDownComponent::Release(void) {
    super::Release();
    _move_com.reset();
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
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionJumpDownState);

    auto velocity_com = super::GetVelocityComponent();
    velocity_com->SetGravity(2.0f);
    return true;
}