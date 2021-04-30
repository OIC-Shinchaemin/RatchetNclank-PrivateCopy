#include "PlayerJumpDownComponent.h"

#include "PlayerStateComponent.h"
#include "../VelocityComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"


void my::PlayerJumpDownComponent::InputJumpVelocity(float speed) {
    if (auto velocity_com = _velocity_com.lock()) {
        //auto accele = Mof::CVector3(0.0f, speed, 0.0f);
        //auto rotate = super::GetOwner()->GetRotate();
        //accele.RotateAround(Mof::CVector3(), rotate);
        auto v = velocity_com->GetVelocity();
        v.y = speed;
        velocity_com->SetVelocity(v);
    } // if
}

my::PlayerJumpDownComponent::PlayerJumpDownComponent(int priority) :
    super(priority),
    _jump_speed_max(20.0f),
    _jump_speed(_jump_speed_max),
    _jump_decrase(1.0f),
    _state_com(),
    _velocity_com(),
    _motion_state_com() {
}

my::PlayerJumpDownComponent::PlayerJumpDownComponent(const PlayerJumpDownComponent& obj) :
    super(obj._priority),
    _jump_speed_max(obj._jump_speed_max),
    _jump_speed(obj._jump_speed),
    _jump_decrase(obj._jump_decrase),
    _state_com(),
    _velocity_com(),
    _motion_state_com() {
}

my::PlayerJumpDownComponent::~PlayerJumpDownComponent() {
}

std::string my::PlayerJumpDownComponent::GetType(void) const {
    return "PlayerJumpDownComponent";
}

bool my::PlayerJumpDownComponent::Initialize(void) {
    super::Initialize();

    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::PlayerJumpDownComponent::Update(float delta_time) {
    puts("PlayerJumpDownComponent");
    return true;
}

bool my::PlayerJumpDownComponent::Release(void) {
    super::Release();
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
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("PlayerMotionJumpDownState");
    } // if
    return true;
}