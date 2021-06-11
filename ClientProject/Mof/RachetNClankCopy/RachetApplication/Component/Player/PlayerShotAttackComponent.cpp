#include "PlayerShotAttackComponent.h"

#include "../../Actor/Character/Player.h"
#include "PlayerMoveComponent.h"


rachet::PlayerShotAttackComponent::PlayerShotAttackComponent(int priority) :
    super(priority),
    _weapon(),
    _input_info(),
    _move_com() {
}

rachet::PlayerShotAttackComponent::PlayerShotAttackComponent(const PlayerShotAttackComponent& obj) :
    super(obj),
    _weapon(),
    _input_info(),
    _move_com() {
}

rachet::PlayerShotAttackComponent::~PlayerShotAttackComponent() {
}

std::string rachet::PlayerShotAttackComponent::GetType(void) const {
    return "PlayerShotAttackComponent";
}

std::string_view rachet::PlayerShotAttackComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionShotAttackState;
}

bool rachet::PlayerShotAttackComponent::Initialize(void) {
    super::Initialize();
    _move_com = super::GetOwner()->GetComponent<rachet::ActionComponent>()->GetComponent<rachet::PlayerMoveComponent>();
    return true;
}

bool rachet::PlayerShotAttackComponent::Input(void) {
    if (auto move_com = _move_com.lock()) {
        _input_info.move_flag = move_com->AquireInputData(_input_info.in, _input_info.move_angle);
        if (_input_info.move_flag) {
            _input_info.in = math::Rotate(_input_info.in.x, _input_info.in.y, math::ToRadian(_input_info.move_angle));
            //this->Move(_move_speed, _angular_speed, std::atan2(-_input_info.in.y, _input_info.in.x) - math::kHalfPi);
        } // if
    } // if
    auto owner = std::dynamic_pointer_cast<rachet::Player>(super::GetOwner());
    if (auto weapon = owner->GetCurrentMechanical()) {
        if (weapon->IsAction() && weapon->CanFire()) {
            auto pos = weapon->GetPosition();
            auto rotate = weapon->GetRotate();
            weapon->Fire(def::Transform(pos, rotate));
        } // if
    } // if

    if (::g_pInput->IsKeyPull(MOFKEY_M) || ::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_B)) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionIdleState);
    } // if

    return true;
}

bool rachet::PlayerShotAttackComponent::Update(float delta_time) {
    if (auto move_com = _move_com.lock()) {
        if (_input_info.move_flag) {
            float move_speed = 1.7f; float angular_speed = 3.3f;
            move_com->Move(move_speed, angular_speed, std::atan2(-_input_info.in.y, _input_info.in.x) - math::kHalfPi);
            //_input_info.in = math::Rotate(_input_info.in.x, _input_info.in.y, math::ToRadian(_input_info.move_angle));
        } // if
    } // if

    /*
    auto owner = std::dynamic_pointer_cast<rachet::Player>(super::GetOwner());
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
    */

    _input_info.Reset();
    return true;
}
bool rachet::PlayerShotAttackComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerShotAttackComponent::Clone(void) {
    return std::make_shared<rachet::PlayerShotAttackComponent>(*this);
}

bool rachet::PlayerShotAttackComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionShotAttackState);

    auto owner = std::dynamic_pointer_cast<rachet::Player>(super::GetOwner());
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