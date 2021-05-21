#include "PlayerJumpLandingComponent.h"

#include "PlayerMoveComponent.h"


my::PlayerJumpLandingComponent::PlayerJumpLandingComponent(int priority) :
    super(priority),
    _move_com() {
}

my::PlayerJumpLandingComponent::PlayerJumpLandingComponent(const PlayerJumpLandingComponent& obj) :
    super(obj),
    _move_com() {
}

my::PlayerJumpLandingComponent::~PlayerJumpLandingComponent() {
}

std::string my::PlayerJumpLandingComponent::GetType(void) const {
    return "PlayerJumpLandingComponent";
}

std::string_view my::PlayerJumpLandingComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpLandingState;
}

bool my::PlayerJumpLandingComponent::Initialize(void) {
    super::Initialize();
    _move_com = super::GetOwner()->GetComponent<my::PlayerMoveComponent>();
    return true;
}

bool my::PlayerJumpLandingComponent::Update(float delta_time) {
    auto move_com = _move_com.lock();

    Mof::CVector2 in;
    float move_angle;

    // flag
    if (move_com->AquireInputData(in, move_angle)) {
        float move_speed = 1.7f; float angular_speed = 3.3f;
        in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
        move_com->Move(move_speed, angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
    } // if

    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_X) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_A)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpSetState);
    } // if
    return true;
}

bool my::PlayerJumpLandingComponent::Release(void) {
    super::Release();
    _move_com.reset();
    return true;
}

std::shared_ptr<my::Component> my::PlayerJumpLandingComponent::Clone(void) {
    return std::make_shared<my::PlayerJumpLandingComponent>(*this);
}

bool my::PlayerJumpLandingComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionJumpLandingState);

    auto velocity_com = super::GetVelocityComponent();
    velocity_com->SetGravity(9.8f);
    return true;
}