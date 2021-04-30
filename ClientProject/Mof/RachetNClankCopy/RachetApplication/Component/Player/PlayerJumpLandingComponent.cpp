#include "PlayerJumpLandingComponent.h"

#include "../../State/PlayerAction/PlayerActionStateDefine.h"
#include "PlayerStateComponent.h"
#include "../VelocityComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"


my::PlayerJumpLandingComponent::PlayerJumpLandingComponent(int priority) :
    super(priority),
    _velocity_com(),
    _motion_com(),
    _motion_state_com(),
    _state_com() {
}

my::PlayerJumpLandingComponent::PlayerJumpLandingComponent(const PlayerJumpLandingComponent& obj) :
    super(obj._priority),
    _velocity_com(),
    _motion_com(),
    _motion_state_com(),
    _state_com() {
}

my::PlayerJumpLandingComponent::~PlayerJumpLandingComponent() {
}

std::string my::PlayerJumpLandingComponent::GetType(void) const {
    return "PlayerJumpLandingComponent";
}

bool my::PlayerJumpLandingComponent::Initialize(void) {
    super::Initialize();

    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::PlayerJumpLandingComponent::Update(float delta_time) {
    puts("PlayerJumpLandingComponent");

    auto motion_com = _motion_com.lock();
    auto state_com = _state_com.lock();

    if (motion_com->IsEndMotion()) {
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

bool my::PlayerJumpLandingComponent::Release(void) {
    super::Release();
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
    if (auto velocity_com = _velocity_com.lock()) {
        velocity_com->SetGravity(3.8f);
    } // if
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("PlayerMotionJumpLandingState");
    } // if
    return true;
}