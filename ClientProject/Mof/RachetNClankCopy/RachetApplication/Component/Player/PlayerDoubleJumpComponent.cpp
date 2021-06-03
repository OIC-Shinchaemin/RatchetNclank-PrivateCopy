#include "PlayerDoubleJumpComponent.h"

#include "PlayerMoveComponent.h"


void my::PlayerDoubleJumpComponent::InputJumpVelocity(float speed) {
    auto velocity_com = super::GetVelocityComponent();
    auto v = velocity_com->GetVelocity();
    v.y = speed;
    velocity_com->SetVelocity(v);
}

my::PlayerDoubleJumpComponent::PlayerDoubleJumpComponent(int priority) :
    super(priority),
    _jump_speed(0.0f),
    _jump_decrase(0.4f),
    _move_com() {
}

my::PlayerDoubleJumpComponent::PlayerDoubleJumpComponent(const PlayerDoubleJumpComponent& obj) :
    super(obj),
    _jump_speed(0.0f),
    _jump_decrase(obj._jump_decrase),
    _move_com() {
}

my::PlayerDoubleJumpComponent::~PlayerDoubleJumpComponent() {
}

std::string my::PlayerDoubleJumpComponent::GetType(void) const {
    return "PlayerDoubleJumpComponent";
}

std::string_view my::PlayerDoubleJumpComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionDoubleJumpState;
}

void my::PlayerDoubleJumpComponent::SetJumpSpeed(float speed) {
    this->_jump_speed = speed;
}

bool my::PlayerDoubleJumpComponent::Initialize(void) {
    super::Initialize();
    _move_com = super::GetOwner()->GetComponent<my::ActionComponent>()->GetComponent<my::PlayerMoveComponent>();
    return true;
}

bool my::PlayerDoubleJumpComponent::Input(void) {
    return false;
}

bool my::PlayerDoubleJumpComponent::Update(float delta_time) {      
    if (0.0f < std::abs(_jump_speed)) {
        this->InputJumpVelocity(_jump_speed);
    } // if
    Mof::CVector2 in;
    float move_angle;
    bool jump_flag = false;

    // flag
    auto move_com = _move_com.lock();
    if (move_com->AquireInputData(in, move_angle)) {
        float move_speed = 1.7f; float angular_speed = 3.3f;
        in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
        move_com->Move(move_speed, angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
    } // if

    _jump_speed -= _jump_decrase;
    if (_jump_speed < 0.0f) {
        _jump_speed = 0.0f;
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpDownState);
    } // if
    return true;
}

bool my::PlayerDoubleJumpComponent::Release(void) {
    super::Release();
    _move_com.reset();
    return true;
}

std::shared_ptr<my::Component> my::PlayerDoubleJumpComponent::Clone(void) {
    return std::make_shared<my::PlayerDoubleJumpComponent>(*this);
}

bool my::PlayerDoubleJumpComponent::Start(void) {
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