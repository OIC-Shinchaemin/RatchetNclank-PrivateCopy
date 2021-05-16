#include "PlayerDeadComponent.h"

#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"


my::PlayerDeadComponent::PlayerDeadComponent(int priority) :
    super(priority),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerDeadComponent::PlayerDeadComponent(const PlayerDeadComponent& obj) :
    super(obj._priority),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerDeadComponent::~PlayerDeadComponent() {
}

std::string my::PlayerDeadComponent::GetType(void) const {
    return "PlayerDeadComponent";
}

std::string_view my::PlayerDeadComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionDeadState;
}

bool my::PlayerDeadComponent::Initialize(void) {
    super::Initialize();

    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::PlayerDeadComponent::Update(float delta_time) {
    if (auto motion_com = _motion_com.lock()) {
        if (motion_com->IsEndMotion()) {
            super::GetOwner()->End();
        } // if
    } // if
    return true;
}

bool my::PlayerDeadComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerDeadComponent::Clone(void) {
    return std::make_shared<my::PlayerDeadComponent>(*this);
}

bool my::PlayerDeadComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionDeadState);
    } // if
    return true;
}