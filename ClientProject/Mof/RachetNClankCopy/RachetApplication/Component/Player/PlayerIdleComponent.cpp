#include "PlayerIdleComponent.h"

#include "../../Gamepad.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionStateComponent.h"


void my::PlayerIdleComponent::ChageState(const std::string& name) {
    if (auto state_com = _state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::PlayerIdleComponent::PlayerIdleComponent(int priority) :
    super(priority),
    _velocity_com(),
    _state_com(),
    _motion_state_com() {
}

my::PlayerIdleComponent::PlayerIdleComponent(const PlayerIdleComponent& obj) :
    super(obj),
    _velocity_com(),
    _state_com(),
    _motion_state_com() {
}

my::PlayerIdleComponent::~PlayerIdleComponent() {
}

std::string my::PlayerIdleComponent::GetType(void) const {
    return "PlayerIdleComponent";
}

std::string_view my::PlayerIdleComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionIdleState;
}

bool my::PlayerIdleComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::PlayerIdleComponent::Update(float delta_time) {
    float h = ::g_pGamepad->GetStickHorizontal(); float v = ::g_pGamepad->GetStickVertical();
    float threshold = 0.5f;
    auto stick = Mof::CVector2(h, v);

    if (::g_pInput->IsKeyHold(MOFKEY_W) ||
        ::g_pInput->IsKeyHold(MOFKEY_A) ||
        ::g_pInput->IsKeyHold(MOFKEY_S) ||
        ::g_pInput->IsKeyHold(MOFKEY_D) ||
        stick.Length() > threshold) {
        this->ChageState(state::PlayerActionStateType::kPlayerActionMoveState);
    } // if
    else if (::g_pInput->IsKeyPush(MOFKEY_X) ||
             ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_A)) {
        this->ChageState(state::PlayerActionStateType::kPlayerActionJumpSetState);
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_Z) ||
             ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        this->ChageState(state::PlayerActionStateType::kPlayerActionMeleeAttackOneState);
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_U) || 
             (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X) && ::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_R_BTN))) {
        this->ChageState(state::PlayerActionStateType::kPlayerActionThrowAttackSetState);
    } // else if



    return true;
}

bool my::PlayerIdleComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerIdleComponent::Clone(void) {
    return std::make_shared<my::PlayerIdleComponent>(*this);
}

bool my::PlayerIdleComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::PlayerMotionStateType::kPlayerMotionIdleState);
    } // if
    return true;
}