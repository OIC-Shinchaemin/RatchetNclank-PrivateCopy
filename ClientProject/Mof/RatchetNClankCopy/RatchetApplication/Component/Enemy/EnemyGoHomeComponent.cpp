#include "EnemyGoHomeComponent.h"

#include "../VelocityComponent.h"
#include "EnemyStateComponent.h"
#include "../MotionStateComponent.h"
#include "EnemyComponent.h"
#include "../../State/EnemyActionStateDefine.h"


void ratchet::component::enemy::EnemyGoHomeComponent::InputMoveVelocity(float speed) {
    if (auto velocity_com = _velocity_com.lock()) {
        auto accele = Mof::CVector3(0.0f, 0.0f, -speed);
        auto rotate = super::GetOwner()->GetRotate();
        accele.RotateAround(Mof::CVector3(), rotate);

        velocity_com->AddVelocityForce(accele);
    } // if
}

void ratchet::component::enemy::EnemyGoHomeComponent::InputMoveAngularVelocity(float angle, float speed) {
    if (auto velocity_com = _velocity_com.lock()) {

        float angle_y = angle;
        if (math::kTwoPi <= angle_y) {
            angle_y -= math::kTwoPi;
        } // if
        else if (angle_y <= 0.0f) {
            angle_y += math::kTwoPi;
        } // else if

        auto rotate = super::GetOwner()->GetRotate();
        // ç∑ï™äpìx
        angle_y -= rotate.y;
        if (math::kPi < angle_y) {
            angle_y -= math::kTwoPi;
        } // if
        else if (angle_y < -math::kPi) {
            angle_y += math::kTwoPi;
        } // else if

        auto accele = Mof::CVector3(0.0f, angle_y * speed, 0.0f);
        velocity_com->AddAngularVelocityForce(accele);
    } // if
}

ratchet::component::enemy::EnemyGoHomeComponent::EnemyGoHomeComponent(int priority) :
    super(priority),
    _move_speed(0.0f),
    _angular_speed(0.0f),
    _ideal_angle(0.0f),
    _velocity_com(),
    _motion_state_com() {
}

ratchet::component::enemy::EnemyGoHomeComponent::EnemyGoHomeComponent(const EnemyGoHomeComponent& obj) :
    super(obj),
    _move_speed(obj._move_speed),
    _angular_speed(obj._angular_speed),
    _ideal_angle(obj._ideal_angle),
    _velocity_com(),
    _motion_state_com() {
}

ratchet::component::enemy::EnemyGoHomeComponent::~EnemyGoHomeComponent() {
}

void ratchet::component::enemy::EnemyGoHomeComponent::SetMoveSpeed(float speed) {
    this->_move_speed = speed;
}

void ratchet::component::enemy::EnemyGoHomeComponent::SetAngularSpeed(float speed) {
    this->_angular_speed = speed;
}

void ratchet::component::enemy::EnemyGoHomeComponent::SetIdealAngle(float radian) {
    this->_ideal_angle = radian;
}

std::string ratchet::component::enemy::EnemyGoHomeComponent::GetType(void) const {
    return "EnemyGoHomeComponent";
}

std::string_view ratchet::component::enemy::EnemyGoHomeComponent::GetStateType(void) const {
    return state::EnemyActionStateType::kEnemyActionGoHomeState;
}

bool ratchet::component::enemy::EnemyGoHomeComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    _action_state_com = super::GetOwner()->GetComponent<ratchet::component::enemy::EnemyStateComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<ratchet::component::MotionStateComponent>();
    _ENEMY_com = super::GetOwner()->GetComponent<ratchet::component::enemy::EnemyComponent>();
    return true;
}

bool ratchet::component::enemy::EnemyGoHomeComponent::Update(float delta_time) {
    Mof::CVector3 target_pos = super::GetOwner()->GetPosition();
    if (auto ENEMY_com = _ENEMY_com.lock()) {
        if (auto target = ENEMY_com->GetTarget().lock()) {
            target_pos = target->GetPosition();
        } // if
        /*
        else {
            if (auto state_com = _action_state_com.lock()) {
                if (state_com->CanTransition(state::EnemyActionStateType::kEnemyActionGoHomeState)) {
                    state_com->ChangeState(state::EnemyActionStateType::kEnemyActionGoHomeState);
                } // if
            } // if
        } // else
        */
    } // if

    Mof::CVector3 target = super::GetOwner()->GetInitialPosition();
    float speed = 1.2f;
    float angular_speed = 1.0f;

    float tilt = 1.0f;
    Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);
    auto dir = target - super::GetOwner()->GetPosition();
    float angle = std::atan2(dir.z, dir.x);
    in = math::Rotate(in.x, in.y, angle);

    this->SetMoveSpeed(speed);
    this->SetAngularSpeed(angular_speed);
    this->SetIdealAngle(std::atan2(-in.y, in.x) - math::kHalfPi);

    ///////

    this->InputMoveAngularVelocity(_ideal_angle, _angular_speed);
    this->InputMoveVelocity(_move_speed);
    return true;
}

bool ratchet::component::enemy::EnemyGoHomeComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::enemy::EnemyGoHomeComponent::Clone(void) {
    return std::make_shared<ratchet::component::enemy::EnemyGoHomeComponent>(*this);
}

bool ratchet::component::enemy::EnemyGoHomeComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("EnemyMotionMoveState");
    } // if
    return true;
}