#include "PlayerMeleeAttackThreeComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerAction/PlayerActionStateDefine.h"
#include "../../State/PlayerMotion/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"


void my::PlayerMeleeAttackThreeComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::PlayerMeleeAttackThreeComponent::PlayerMeleeAttackThreeComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerMeleeAttackThreeComponent::PlayerMeleeAttackThreeComponent(const PlayerMeleeAttackThreeComponent& obj) :
    super(obj._priority),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerMeleeAttackThreeComponent::~PlayerMeleeAttackThreeComponent() {
}

std::string my::PlayerMeleeAttackThreeComponent::GetType(void) const {
    return "PlayerMeleeAttackThreeComponent";
}

bool my::PlayerMeleeAttackThreeComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::PlayerMeleeAttackThreeComponent::Update(float delta_time) {
    puts("PlayerMeleeAttackThreeComponent");
    auto state_com = _state_com.lock();
    auto motion_com = _motion_com.lock();
    auto motion_state_com = _motion_state_com.lock();

    if (motion_com->IsEndMotion()) {
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

bool my::PlayerMeleeAttackThreeComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerMeleeAttackThreeComponent::Clone(void) {
    return std::make_shared<my::PlayerMeleeAttackThreeComponent>(*this);
}

bool my::PlayerMeleeAttackThreeComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackThreeState);
    } // if
    return true;
}