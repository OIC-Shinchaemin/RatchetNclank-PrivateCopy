#include "PlayerMeleeAttackThreeEndComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"


void my::PlayerMeleeAttackThreeEndComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::PlayerMeleeAttackThreeEndComponent::PlayerMeleeAttackThreeEndComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerMeleeAttackThreeEndComponent::PlayerMeleeAttackThreeEndComponent(const PlayerMeleeAttackThreeEndComponent& obj) :
    super(obj._priority),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerMeleeAttackThreeEndComponent::~PlayerMeleeAttackThreeEndComponent() {
}

std::string my::PlayerMeleeAttackThreeEndComponent::GetType(void) const {
    return "PlayerMeleeAttackThreeEndComponent";
}

std::string_view my::PlayerMeleeAttackThreeEndComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionMeleeAttackThreeEndState;
}

bool my::PlayerMeleeAttackThreeEndComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::PlayerMeleeAttackThreeEndComponent::Update(float delta_time) {
    auto state_com = _state_com.lock();
    auto motion_com = _motion_com.lock();
    auto motion_state_com = _motion_state_com.lock();


    if (::g_pInput->IsKeyPush(MOFKEY_Z) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
//        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionMeleeAttackTwoState);
    } // if

    if (motion_com->IsEndMotion()) {
        state_com->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if
    return true;
}

bool my::PlayerMeleeAttackThreeEndComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerMeleeAttackThreeEndComponent::Clone(void) {
    return std::make_shared<my::PlayerMeleeAttackThreeEndComponent>(*this);
}

bool my::PlayerMeleeAttackThreeEndComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackThreeEndState);
    } // if
    return true;
}