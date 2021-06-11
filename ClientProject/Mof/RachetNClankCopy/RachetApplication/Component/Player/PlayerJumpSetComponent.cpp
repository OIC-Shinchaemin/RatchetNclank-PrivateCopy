#include "PlayerJumpSetComponent.h"

#include "PlayerMoveComponent.h"
#include "PlayerJumpUpComponent.h"


rachet::PlayerJumpSetComponent::PlayerJumpSetComponent(int priority) :
    super(priority),
    _jump_speed(0.0f),
    _jump_speed_first(6.0f),
    _jump_speed_increase(0.6f),
    _move_com(),
    _jump_com() {
}

rachet::PlayerJumpSetComponent::PlayerJumpSetComponent(const PlayerJumpSetComponent& obj) :
    super(obj),
    _jump_speed(0.0f),
    _jump_speed_first(obj._jump_speed_first),
    _jump_speed_increase(obj._jump_speed_increase),
    _move_com(),
    _jump_com() {
}

rachet::PlayerJumpSetComponent::~PlayerJumpSetComponent() {
}

std::string rachet::PlayerJumpSetComponent::GetType(void) const {
    return "PlayerJumpSetComponent";
}

std::string_view rachet::PlayerJumpSetComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionJumpSetState;
}

bool rachet::PlayerJumpSetComponent::Initialize(void) {
    super::Initialize();
    _move_com = super::GetOwner()->GetComponent<rachet::ActionComponent>()->GetComponent<rachet::PlayerMoveComponent>();
    _jump_com = super::GetOwner()->GetComponent<rachet::ActionComponent>()->GetComponent<rachet::PlayerJumpUpComponent>();
    return true;
}

bool rachet::PlayerJumpSetComponent::Input(void) {
    ;

    if (::g_pInput->IsKeyHold(MOFKEY_J) ||
        ::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_A)) {
        _jump_speed += _jump_speed_increase;
    } // else if

    // flag
    auto& [in, move_angle, move_flag] = _input_info;

    if (auto move_com = _move_com.lock()) {
        move_flag = move_com->AquireInputData(in, move_angle);
        if (move_flag) {
            float move_speed = 1.7f; float angular_speed = 3.3f;
            in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
        } // if
    } // if
    return false;
}

bool rachet::PlayerJumpSetComponent::Update(float delta_time) {
    auto move_com = _move_com.lock();



    if (_input_info.move_flag) {
        auto& in = _input_info.in;
        float move_speed = 1.7f; float angular_speed = 3.3f;
        move_com->Move(move_speed, angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
        //in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
    } // if




    ///////////
    if (super::IsEndMotion()) {
        _jump_com.lock()->SetJumpSpeed(_jump_speed);
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpUpState);
    } // if

    _input_info.Reset();
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerJumpSetComponent::Clone(void) {
    return std::make_shared<rachet::PlayerJumpSetComponent>(*this);
}

bool rachet::PlayerJumpSetComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionJumpSetState);
    _jump_speed = _jump_speed_first;
    return true;
}