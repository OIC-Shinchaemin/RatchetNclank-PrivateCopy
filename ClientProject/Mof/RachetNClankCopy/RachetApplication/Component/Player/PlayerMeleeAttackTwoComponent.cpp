#include "PlayerMeleeAttackTwoComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerAction/PlayerActionStateDefine.h"
#include "../../State/PlayerMotion/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"


void my::PlayerMeleeAttackTwoComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::PlayerMeleeAttackTwoComponent::PlayerMeleeAttackTwoComponent(int priority) :
    super(priority),
    _next_reserve(false),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerMeleeAttackTwoComponent::PlayerMeleeAttackTwoComponent(const PlayerMeleeAttackTwoComponent& obj) :
    super(obj._priority),
    _next_reserve(false),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerMeleeAttackTwoComponent::~PlayerMeleeAttackTwoComponent() {
}

std::string my::PlayerMeleeAttackTwoComponent::GetType(void) const {
    return "PlayerMeleeAttackTwoComponent";
}

bool my::PlayerMeleeAttackTwoComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::PlayerMeleeAttackTwoComponent::Update(float delta_time) {
    puts("PlayerMeleeAttackTwoComponent");
    auto state_com = _state_com.lock();
    auto motion_com = _motion_com.lock();
    auto motion_state_com = _motion_state_com.lock();


    if (::g_pInput->IsKeyPush(MOFKEY_Z) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        _next_reserve = true;
    } // if

    if (motion_com->IsEndMotion()) {
        if (_next_reserve) {
            state_com->ChangeState(state::PlayerActionStateType::kPlayerActionMeleeAttackThreeState);
        } // if
        else {
            state_com->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
        } // else
    } // if
    return true;
}

bool my::PlayerMeleeAttackTwoComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerMeleeAttackTwoComponent::Clone(void) {
    return std::make_shared<my::PlayerMeleeAttackTwoComponent>(*this);
}

bool my::PlayerMeleeAttackTwoComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    _next_reserve = false;
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackTwoState);
    } // if
    return true;
}