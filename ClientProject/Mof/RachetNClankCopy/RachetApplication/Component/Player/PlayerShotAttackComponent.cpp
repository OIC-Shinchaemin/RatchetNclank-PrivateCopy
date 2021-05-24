#include "PlayerShotAttackComponent.h"

#include "../../Actor/Character/Player.h"


my::PlayerShotAttackComponent::PlayerShotAttackComponent(int priority) :
    super(priority),
    _weapon() {
}

my::PlayerShotAttackComponent::PlayerShotAttackComponent(const PlayerShotAttackComponent& obj) :
    super(obj),
    _weapon() {
}

my::PlayerShotAttackComponent::~PlayerShotAttackComponent() {
}

std::string my::PlayerShotAttackComponent::GetType(void) const {
    return "PlayerShotAttackComponent";
}

std::string_view my::PlayerShotAttackComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionShotAttackState;
}

bool my::PlayerShotAttackComponent::Initialize(void) {
    super::Initialize();
    return true;
}

bool my::PlayerShotAttackComponent::Update(float delta_time) {
    if (::g_pInput->IsKeyPull(MOFKEY_V) || ::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_B)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if

    auto owner = std::dynamic_pointer_cast<my::Player>(super::GetOwner());
    if (auto weapon = owner->GetCurrentMechanical()) {
        puts("GetCurrentMechanical");
        if (weapon->IsAction() && weapon->CanFire()) {
        //if (weapon->IsAction() ) {
            puts("weapon->IsAction() && weapon->CanFire()");

            auto pos = super::GetOwner()->GetPosition();
            auto rotate = super::GetOwner()->GetRotate();
            _weapon.lock()->Fire(def::Transform(pos, rotate));

        } // if
    } // if
    return true;
}

bool my::PlayerShotAttackComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerShotAttackComponent::Clone(void) {
    return std::make_shared<my::PlayerShotAttackComponent>(*this);
}

bool my::PlayerShotAttackComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionShotAttackState);

    auto owner = std::dynamic_pointer_cast<my::Player>(super::GetOwner());
    _weapon = owner->GetCurrentMechanical();
    owner->OnNotify(_weapon.lock());
    auto pos = super::GetOwner()->GetPosition();
    auto rotate = super::GetOwner()->GetRotate();
    _weapon.lock()->Fire(def::Transform(pos, rotate));
    //weapon->Fire();
    //if (auto weapon_com = _weapon_com.lock()) {
        //weapon_com->Activate();
    //} // if
    return true;
}

bool my::PlayerShotAttackComponent::End(void) {
    super::End();
    //if (auto weapon_com = _weapon_com.lock()) {
        //weapon_com->Inactivate();
    //} // if
    return true;
}