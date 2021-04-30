#include "PlayerJumpSetComponent.h"

#include "../../State/PlayerAction/PlayerActionStateDefine.h"
#include "PlayerStateComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"


my::PlayerJumpSetComponent::PlayerJumpSetComponent(int priority) :
    super(priority),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerJumpSetComponent::PlayerJumpSetComponent(const PlayerJumpSetComponent& obj) :
    super(obj._priority),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerJumpSetComponent::~PlayerJumpSetComponent() {
}

std::string my::PlayerJumpSetComponent::GetType(void) const {
    return "PlayerJumpSetComponent";
}

bool my::PlayerJumpSetComponent::Initialize(void) {
    super::Initialize();

    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::PlayerJumpSetComponent::Update(float delta_time) {
    auto state_com = _state_com.lock();
    auto motion_com = _motion_com.lock();

    if (motion_com->IsEndMotion()) {
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionJumpUpState);
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
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("PlayerMotionJumpSetState");
    } // if
    return true;
}