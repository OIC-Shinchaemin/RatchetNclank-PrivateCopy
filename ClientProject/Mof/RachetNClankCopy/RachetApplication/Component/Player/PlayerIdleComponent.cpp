#include "PlayerIdleComponent.h"

#include "../../Actor/Character/Player.h"


rachet::PlayerIdleComponent::PlayerIdleComponent(int priority) :
    super(priority) {
}

rachet::PlayerIdleComponent::PlayerIdleComponent(const PlayerIdleComponent& obj) :
    super(obj) {
}

rachet::PlayerIdleComponent::~PlayerIdleComponent() {
}

std::string rachet::PlayerIdleComponent::GetType(void) const {
    return "PlayerIdleComponent";
}

std::string_view rachet::PlayerIdleComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionIdleState;
}

bool rachet::PlayerIdleComponent::Input(void) {
    float horizontal = ::g_pGamepad->GetStickHorizontal();
    float vertical = ::g_pGamepad->GetStickVertical();
    float threshold = 0.5f;
    auto stick = Mof::CVector2(horizontal, vertical);

    if (::g_pInput->IsKeyHold(MOFKEY_W) || ::g_pInput->IsKeyHold(MOFKEY_A) ||
        ::g_pInput->IsKeyHold(MOFKEY_S) || ::g_pInput->IsKeyHold(MOFKEY_D) ||
        stick.Length() > threshold) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMoveState);
    } // if
    else if (::g_pInput->IsKeyPush(MOFKEY_J) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_A)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpSetState);
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_N) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_X)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionMeleeAttackOneState);
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_M) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_B)) {
        auto owner = std::dynamic_pointer_cast<rachet::Player>(super::GetOwner());
        if (owner->GetCurrentMechanical()) {
            super::ChangeActionState(state::PlayerActionStateType::kPlayerActionShotAttackState);
        } // if
    } // else if
    else if (::g_pInput->IsKeyPush(MOFKEY_U) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_R_BTN)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionCrouchState);
    } // else if
    
    return true;
}

bool rachet::PlayerIdleComponent::Update(float delta_time) {
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerIdleComponent::Clone(void) {
    return std::make_shared<rachet::PlayerIdleComponent>(*this);
}

bool rachet::PlayerIdleComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionIdleState);
    return true;
}