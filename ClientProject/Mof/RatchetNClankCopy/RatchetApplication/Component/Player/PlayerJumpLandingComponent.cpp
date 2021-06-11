#include "PlayerJumpLandingComponent.h"

#include "PlayerMoveComponent.h"


ratchet::PlayerJumpLandingComponent::PlayerJumpLandingComponent(int priority) :
    super(priority),
    _input_info(),
    _move_com() {
}

ratchet::PlayerJumpLandingComponent::PlayerJumpLandingComponent(const PlayerJumpLandingComponent& obj) :
    super(obj),
    _input_info(),
    _move_com() {
}

ratchet::PlayerJumpLandingComponent::~PlayerJumpLandingComponent() {
}

std::string ratchet::PlayerJumpLandingComponent::GetType(void) const {
    return "PlayerJumpLandingComponent";
}

std::string_view ratchet::PlayerJumpLandingComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpLandingState;
}

bool ratchet::PlayerJumpLandingComponent::Initialize(void) {
    super::Initialize();
    _move_com = super::GetOwner()->GetComponent<ratchet::ActionComponent>()->GetComponent<ratchet::PlayerMoveComponent>();
    return true;
}

bool ratchet::PlayerJumpLandingComponent::Input(void) {
    auto move_com = _move_com.lock();
    auto& [in, move_angle, move_flag] = _input_info;
    move_flag = move_com->AquireInputData(in, move_angle);

    if (move_flag) {
        //float move_speed = 1.7f; float angular_speed = 3.3f;
        in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
        //move_com->Move(move_speed, angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
    } // if

    return true;
}

bool ratchet::PlayerJumpLandingComponent::Update(float delta_time) {
    auto move_com = _move_com.lock();

    //Mof::CVector2 in;
    //float move_angle;

    auto& [in, move_angle, move_flag] = _input_info;
    if (move_flag) {
        float move_speed = 1.7f; float angular_speed = 3.3f;
        //in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
        move_com->Move(move_speed, angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
    } // if

    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_X) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_A)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpSetState);
    } // if
    _input_info.Reset();

    return true;
}

bool ratchet::PlayerJumpLandingComponent::Release(void) {
    super::Release();
    _move_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerJumpLandingComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerJumpLandingComponent>(*this);
}

bool ratchet::PlayerJumpLandingComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionJumpLandingState);

    auto velocity_com = super::GetVelocityComponent();
    velocity_com->SetGravity(9.8f);
    return true;
}