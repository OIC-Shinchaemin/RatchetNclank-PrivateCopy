#include "PlayerMeleeAttackTwoEndComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerAction/PlayerActionStateDefine.h"
#include "../../State/PlayerMotion/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"


void my::PlayerMeleeAttackTwoEndComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::PlayerMeleeAttackTwoEndComponent::PlayerMeleeAttackTwoEndComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerMeleeAttackTwoEndComponent::PlayerMeleeAttackTwoEndComponent(const PlayerMeleeAttackTwoEndComponent& obj) :
    super(obj._priority),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerMeleeAttackTwoEndComponent::~PlayerMeleeAttackTwoEndComponent() {
}

std::string my::PlayerMeleeAttackTwoEndComponent::GetType(void) const {
    return "PlayerMeleeAttackTwoEndComponent";
}

bool my::PlayerMeleeAttackTwoEndComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::PlayerMeleeAttackTwoEndComponent::Update(float delta_time) {
    puts("PlayerMeleeAttackTwoEndComponent");
    auto state_com = _state_com.lock();
    auto motion_com = _motion_com.lock();
    auto motion_state_com = _motion_state_com.lock();


    if (::g_pInput->IsKeyPush(MOFKEY_Z) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionMeleeAttackThreeState);
    } // if

    if (motion_com->IsEndMotion()) {
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

bool my::PlayerMeleeAttackTwoEndComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerMeleeAttackTwoEndComponent::Clone(void) {
    return std::make_shared<my::PlayerMeleeAttackTwoEndComponent>(*this);
}

bool my::PlayerMeleeAttackTwoEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackTwoEndState);
    } // if
    return true;
}