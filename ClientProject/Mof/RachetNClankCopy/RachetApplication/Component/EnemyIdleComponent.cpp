#include "EnemyIdleComponent.h"

#include "VelocityComponent.h"
#include "MotionStateComponent.h"



void my::EnemyIdleComponent ::InputMoveAngularVelocity(float angle, float speed) {
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

my::EnemyIdleComponent ::EnemyIdleComponent (int priority) :
    super(priority),
    _angular_speed(0.0f),
    _ideal_angle(0.0f),
    _velocity_com(),
    _motion_state_com() {
}

my::EnemyIdleComponent ::EnemyIdleComponent (const EnemyIdleComponent & obj) :
    super(obj._priority),
    _angular_speed(obj._angular_speed),
    _ideal_angle(obj._ideal_angle),
    _velocity_com(),
    _motion_state_com() {
}

my::EnemyIdleComponent ::~EnemyIdleComponent () {
}

void my::EnemyIdleComponent ::SetAngularSpeed(float speed) {
    this->_angular_speed = speed;
}

void my::EnemyIdleComponent ::SetIdealAngle(float radian) {
    this->_ideal_angle = radian;
}

std::string my::EnemyIdleComponent ::GetType(void) const {
    return "EnemyIdleComponent";
}

bool my::EnemyIdleComponent ::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::EnemyIdleComponent ::Update(float delta_time) {
    this->InputMoveAngularVelocity(_ideal_angle, _angular_speed);
    super::End();
    return true;
}

bool my::EnemyIdleComponent ::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::EnemyIdleComponent ::Clone(void) {
    return std::make_shared<my::EnemyIdleComponent >(*this);
}

bool my::EnemyIdleComponent ::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("EnemyMotionIdleState");
    } // if
    return true;
}