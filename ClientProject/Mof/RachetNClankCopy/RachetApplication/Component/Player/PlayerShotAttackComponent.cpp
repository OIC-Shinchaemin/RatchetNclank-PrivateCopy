#include "PlayerShotAttackComponent.h"

#include "../../Actor/Character/Player.h"
#include "PlayerMoveComponent.h"


my::PlayerShotAttackComponent::PlayerShotAttackComponent(int priority) :
    super(priority),
    _weapon(),
    _move_com() {
}

my::PlayerShotAttackComponent::PlayerShotAttackComponent(const PlayerShotAttackComponent& obj) :
    super(obj),
    _weapon(),
    _move_com() {
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
    _move_com = super::GetOwner()->GetComponent<my::PlayerMoveComponent>();
    return true;
}

bool my::PlayerShotAttackComponent::Update(float delta_time) {
    if (auto move_com = _move_com.lock()) {
        Mof::CVector2 in;    float move_angle;
        if (move_com->AquireInputData(in, move_angle)) {
            float move_speed = 1.7f; float angular_speed = 3.3f;
            in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
            move_com->Move(move_speed, angular_speed, std::atan2(-in.y, in.x) - math::kHalfPi);
        } // if
    } // if

    auto owner = std::dynamic_pointer_cast<my::Player>(super::GetOwner());
    if (auto weapon = owner->GetCurrentMechanical()) {
        if (weapon->IsAction() && weapon->CanFire()) {
            auto pos = weapon->GetPosition();
            auto rotate = weapon->GetRotate();
            weapon->Fire(def::Transform(pos, rotate));
        } // if
    } // if

    if (::g_pInput->IsKeyPull(MOFKEY_V) || ::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_B)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
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
    if (auto weapon = owner->GetCurrentMechanical()) {
        owner->OnNotify(weapon);
        if (weapon->IsAction() && weapon->CanFire()) {
            auto pos = weapon->GetPosition();
            auto rotate = owner->GetRotate();
            weapon->Fire(def::Transform(pos, rotate));
        } // if
    } // if
    return true;
}