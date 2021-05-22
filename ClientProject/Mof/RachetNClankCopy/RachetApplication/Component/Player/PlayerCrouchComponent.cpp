#include "PlayerCrouchComponent.h"

#include "PlayerMoveComponent.h"


my::PlayerCrouchComponent::PlayerCrouchComponent(int priority) :
    super(priority),
    _transition_pairs(),
    _angular_speed(),
    _ideal_angle(),
    _move_com() {
}

my::PlayerCrouchComponent::PlayerCrouchComponent(const PlayerCrouchComponent& obj) :
    super(obj),
    _transition_pairs(),
    _angular_speed(2.0f),
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
    _transition_pairs.reserve(2);

    _move_com = super::GetOwner()->GetComponent<my::PlayerMoveComponent>();

    using Type = state::PlayerActionStateType;
    _transition_pairs.push_back(Transition(Type::kPlayerActionIdleState,
                                           []() { return ::g_pInput->IsKeyPull(MOFKEY_U) || ::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_R_BTN); }));

    _transition_pairs.push_back(Transition(Type::kPlayerActionThrowAttackSetState,
                                           []() { return ::g_pInput->IsKeyPush(MOFKEY_Z) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X); }));
    return true;
}

bool my::PlayerCrouchComponent::Update(float delta_time) {
    for (auto& transition : _transition_pairs) {
        if (transition.condition()) {
            auto state = transition.state.data();
            if (super::CanTransitionActionState(state)) {
                super::ChangeActionState(state);
                break;
            } // if
        } // if
    } // for

    if (auto move_com = _move_com.lock()) {
        Mof::CVector2 in;
        if (move_com->AquireInputData(in, _ideal_angle)) {
            in = math::Rotate(in.x, in.y, math::ToRadian(_ideal_angle));
            move_com->Move(0.0f, _angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
        } // if
    } // if
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