#include "PlayerDoubleJumpComponent.h"

#include "PlayerMoveComponent.h"


void ratchet::PlayerDoubleJumpComponent::InputJumpVelocity(float speed) {
    auto velocity_com = super::GetVelocityComponent();
    auto v = velocity_com->GetVelocity();
    v.y = speed;
    velocity_com->SetVelocity(v);
}

ratchet::PlayerDoubleJumpComponent::PlayerDoubleJumpComponent(int priority) :
    super(priority),
    _jump_speed(0.0f),
    _jump_decrase(0.4f),
    _input_info(),
    _move_com() {
}

ratchet::PlayerDoubleJumpComponent::PlayerDoubleJumpComponent(const PlayerDoubleJumpComponent& obj) :
    super(obj),
    _jump_speed(0.0f),
    _jump_decrase(obj._jump_decrase),
    _input_info(),
    _move_com() {
}

ratchet::PlayerDoubleJumpComponent::~PlayerDoubleJumpComponent() {
}

std::string ratchet::PlayerDoubleJumpComponent::GetType(void) const {
    return "PlayerDoubleJumpComponent";
}

std::string_view ratchet::PlayerDoubleJumpComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionDoubleJumpState;
}

void ratchet::PlayerDoubleJumpComponent::SetJumpSpeed(float speed) {
    this->_jump_speed = speed;
}

bool ratchet::PlayerDoubleJumpComponent::Initialize(void) {
    super::Initialize();
    _move_com = super::GetOwner()->GetComponent<ratchet::ActionComponent>()->GetComponent<ratchet::PlayerMoveComponent>();
    return true;
}

bool ratchet::PlayerDoubleJumpComponent::Input(void) {
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

bool ratchet::PlayerDoubleJumpComponent::Update(float delta_time) {      
    if (0.0f < std::abs(_jump_speed)) {
        this->InputJumpVelocity(_jump_speed);
    } // if
//    Mof::CVector2 in;
//    float move_angle;

    // flag
    auto move_com = _move_com.lock();

    auto& [in, move_angle, move_flag] = _input_info;
    if (move_flag) {
        float move_speed = 1.7f; float angular_speed = 3.3f;
        //in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
        move_com->Move(move_speed, angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
    } // if
    /*
    if (move_com->AquireInputData(in, move_angle)) {
        float move_speed = 1.7f; float angular_speed = 3.3f;
        in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
        move_com->Move(move_speed, angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
    } // if
*/

    _jump_speed -= _jump_decrase;
    if (_jump_speed < 0.0f) {
        _jump_speed = 0.0f;
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpDownState);
    } // if
    _input_info.Reset();
    return true;
}

bool ratchet::PlayerDoubleJumpComponent::Release(void) {
    super::Release();
    _move_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerDoubleJumpComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerDoubleJumpComponent>(*this);
}

bool ratchet::PlayerDoubleJumpComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionDoubleJumpState);

    auto velocity_com = super::GetVelocityComponent();
    velocity_com->SetGravity(1.8f);
    
    _jump_speed = 10.0f;
    return true;
}