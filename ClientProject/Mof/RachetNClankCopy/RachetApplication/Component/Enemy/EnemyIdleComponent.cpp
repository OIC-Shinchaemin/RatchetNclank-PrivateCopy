#include "EnemyIdleComponent.h"

#include "../VelocityComponent.h"
#include "../MotionStateComponent.h"
#include "../../State/EnemyActionStateDefine.h"
#include "../../State/EnemyMotionStateDefine.h"


void rachet::EnemyIdleComponent::InputMoveAngularVelocity(float angle, float speed) {
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

rachet::EnemyIdleComponent::EnemyIdleComponent(int priority) :
    super(priority),
    _angular_speed(0.0f),
    _ideal_angle(0.0f),
    _velocity_com(),
    _motion_state_com() {
}

rachet::EnemyIdleComponent::EnemyIdleComponent(const EnemyIdleComponent& obj) :
    super(obj),
    _angular_speed(obj._angular_speed),
    _ideal_angle(obj._ideal_angle),
    _velocity_com(),
    _motion_state_com() {
}

rachet::EnemyIdleComponent ::~EnemyIdleComponent() {
}

void rachet::EnemyIdleComponent::SetAngularSpeed(float speed) {
    this->_angular_speed = speed;
}

void rachet::EnemyIdleComponent::SetIdealAngle(float radian) {
    this->_ideal_angle = radian;
}

float rachet::EnemyIdleComponent::GetIdealAngle(void) const {
    return this->_ideal_angle;
}

std::string rachet::EnemyIdleComponent::GetType(void) const {
    return "EnemyIdleComponent";
}

std::string_view rachet::EnemyIdleComponent::GetStateType(void) const {
    return state::EnemyActionStateType::kEnemyActionIdleState;
}

bool rachet::EnemyIdleComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<rachet::VelocityComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<rachet::MotionStateComponent>();
    return true;
}

bool rachet::EnemyIdleComponent::Update(float delta_time) {
    float tilt = 1.0f;
    Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);
    auto angle_y = math::ToDegree(super::GetOwner()->GetRotate().y);
    in = math::Rotate(in.x, in.y, ut::GenerateRandomF(0.0f, math::kTwoPi));
    float angular_speed = 4.0f;

    this->SetAngularSpeed(angular_speed);
    float angle = this->GetIdealAngle();
    angle += math::ToRadian(0.5f);
    if (math::ToRadian(360.0f) < angle) {
        angle = 0.0f;
    } // if
    this->SetIdealAngle(angle);


    this->InputMoveAngularVelocity(_ideal_angle, _angular_speed);
    return true;
}

bool rachet::EnemyIdleComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::EnemyIdleComponent::Clone(void) {
    return std::make_shared<rachet::EnemyIdleComponent >(*this);
}

bool rachet::EnemyIdleComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::EnemyMotionStateType::kEnemyMotionIdleState);
    } // if
    return true;
}