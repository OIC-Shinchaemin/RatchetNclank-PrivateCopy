#include "PlayerJumpComponent.h"

#include "../VelocityComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"


void my::PlayerJumpComponent::InputJumpVelocity(float speed) {
    if (auto velocity_com = _velocity_com.lock()) {
        //auto accele = Mof::CVector3(0.0f, speed, 0.0f);
        //auto rotate = super::GetOwner()->GetRotate();
        //accele.RotateAround(Mof::CVector3(), rotate);
        auto v = velocity_com->GetVelocity();
        v.y = speed;
        velocity_com->SetVelocity(v);
    } // if
}

my::PlayerJumpComponent::PlayerJumpComponent(int priority) :
    super(priority),
    _jump_speed_max(20.0f),
    _jump_speed(_jump_speed_max),
    _jump_decrase(1.0f),
    _velocity_com(),
    _motion_state_com() {
}

my::PlayerJumpComponent::PlayerJumpComponent(const PlayerJumpComponent& obj) :
    super(obj._priority),
    _jump_speed_max(obj._jump_speed_max),
    _jump_speed(obj._jump_speed),
    _jump_decrase(obj._jump_decrase),
    _velocity_com(),
    _motion_state_com() {
}

my::PlayerJumpComponent::~PlayerJumpComponent() {
}

std::string my::PlayerJumpComponent::GetType(void) const {
    return "PlayerJumpComponent";
}

bool my::PlayerJumpComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::PlayerJumpComponent::Update(float delta_time) {
    if (0.0f < std::abs(_jump_speed)) {
        this->InputJumpVelocity(_jump_speed);
    } // if
    auto motion_com = _motion_com.lock();
    auto motion_state_com = _motion_state_com.lock();
    auto velocity_com = _velocity_com.lock();

    _jump_speed -= _jump_decrase;
    if (_jump_speed < 0.0f) {
        _jump_speed = 0.0f;
        velocity_com->SetGravity(4.8f);
        motion_state_com->ChangeState("PlayerMotionJumpDownState");
    } // if
    else if (motion_com->IsEndMotion()) {
        motion_state_com->ChangeState("PlayerMotionJumpUpState");
        velocity_com->SetGravity(3.8f);
        _jump_speed = _jump_speed_max;
    } // else if
    return true;
}

bool my::PlayerJumpComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerJumpComponent::Clone(void) {
    return std::make_shared<my::PlayerJumpComponent>(*this);
}

bool my::PlayerJumpComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("PlayerMotionJumpSetState");
    } // if
    return true;
}