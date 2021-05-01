#include "PlayerMeleeAttackOneComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerAction/PlayerActionStateDefine.h"
#include "../../State/PlayerMotion/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"
#include "../MotionComponent.h"


void my::PlayerMeleeAttackOneComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::PlayerMeleeAttackOneComponent::PlayerMeleeAttackOneComponent(int priority) :
    super(priority),
    _next_reserve(false),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerMeleeAttackOneComponent::PlayerMeleeAttackOneComponent(const PlayerMeleeAttackOneComponent& obj) :
    super(obj._priority),
    _next_reserve(false),
    _velocity_com(),
    _state_com(),
    _motion_com(),
    _motion_state_com() {
}

my::PlayerMeleeAttackOneComponent::~PlayerMeleeAttackOneComponent() {
}

std::string my::PlayerMeleeAttackOneComponent::GetType(void) const {
    return "PlayerMeleeAttackOneComponent";
}

bool my::PlayerMeleeAttackOneComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::PlayerMeleeAttackOneComponent::Update(float delta_time) {
    puts("PlayerMeleeAttackOneComponent");
    auto state_com = _state_com.lock();
    auto motion_com = _motion_com.lock();
    auto motion_state_com = _motion_state_com.lock();


    if (::g_pInput->IsKeyPush(MOFKEY_Z) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        _next_reserve = true;
    } // if

    if (motion_com->IsEndMotion()) {
        if (_next_reserve) {
            state_com->ChangeState(state::PlayerActionStateType::kPlayerActionMeleeAttackTwoState);
        } // if
        else {
            state_com->ChangeState(state::PlayerActionStateType::kPlayerActionMeleeAttackOneEndState);
        } // else
    } // if
    return true;
}

bool my::PlayerMeleeAttackOneComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerMeleeAttackOneComponent::Clone(void) {
    return std::make_shared<my::PlayerMeleeAttackOneComponent>(*this);
}

bool my::PlayerMeleeAttackOneComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    _next_reserve = false;
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionMeleeAttackOneState);
    } // if
    return true;
}