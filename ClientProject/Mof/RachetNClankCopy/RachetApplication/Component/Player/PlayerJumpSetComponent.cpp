#include "PlayerJumpSetComponent.h"

#include "PlayerMoveComponent.h"
#include "PlayerJumpUpComponent.h"


my::PlayerJumpSetComponent::PlayerJumpSetComponent(int priority) :
    super(priority),
    _jump_speed(0.0f),
    _jump_speed_first(6.0f),
    _jump_speed_increase(0.6f),
    _move_com(),
    _jump_com() {
}

my::PlayerJumpSetComponent::PlayerJumpSetComponent(const PlayerJumpSetComponent& obj) :
    super(obj),
    _jump_speed(0.0f),
    _jump_speed_first(obj._jump_speed_first),
    _jump_speed_increase(obj._jump_speed_increase),
    _move_com(),
    _jump_com() {
}

my::PlayerJumpSetComponent::~PlayerJumpSetComponent() {
}

std::string my::PlayerJumpSetComponent::GetType(void) const {
    return "PlayerJumpSetComponent";
}

std::string_view my::PlayerJumpSetComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpSetState;
}

bool my::PlayerJumpSetComponent::Initialize(void) {
    super::Initialize();
    _move_com = super::GetOwner()->GetComponent<my::ActionComponent>()->GetComponent<my::PlayerMoveComponent>();
    _jump_com = super::GetOwner()->GetComponent<my::ActionComponent>()->GetComponent<my::PlayerJumpUpComponent>();
    return true;
}

bool my::PlayerJumpSetComponent::Update(float delta_time) {
    auto move_com = _move_com.lock();

    if (::g_pInput->IsKeyHold(MOFKEY_X) ||
        ::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_A)) {
        _jump_speed += _jump_speed_increase;
    } // else if


    Mof::CVector2 in;
    float move_angle;
    // flag
    if (move_com->AquireInputData(in, move_angle)) {
        float move_speed = 1.7f; float angular_speed = 3.3f;
        in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
        move_com->Move(move_speed, angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
    } // if

    if (super::IsEndMotion()) {
        _jump_com.lock()->SetJumpSpeed(_jump_speed);
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpUpState);
    } // if
    return true;
}

std::shared_ptr<my::Component> my::PlayerJumpSetComponent::Clone(void) {
    return std::make_shared<my::PlayerJumpSetComponent>(*this);
}

bool my::PlayerJumpSetComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionJumpSetState);
    _jump_speed = _jump_speed_first;
    return true;
}