#include "Idle.h"

#include "My/Core/Math.h"
#include "Character/Enemy.h"


void my::Idle::InputMoveAngularVelocity(float angle, float speed) {
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
    _velocity->AddAngularVelocityForce(accele);
}

bool my::Idle::InactiveCondition(void) const {
    return true;
}

void my::Idle::Execute(float delta_time) {
    this->InputMoveAngularVelocity(_ideal_angle, _angular_speed);
}

my::Idle::Idle() :
    super(),
    _angular_speed(0.0f),
    _ideal_angle(0.0f),
    _velocity() {
}

my::Idle::~Idle() {
}

void my::Idle::SetVelocity(my::Velocity* ptr) {
    this->_velocity = ptr;
}

void my::Idle::SetAngularSpeed(float speed) {
    this->_angular_speed = speed;
}

void my::Idle::SetIdealAngle(float radian) {
    this->_ideal_angle = radian;
}

bool my::Idle::Start(void) {
    if (_active) {
        return false;
    } // if
    _active = true;
    super::GetOwner()->ChangeMotionState("EnemyMotionIdleState");
    return _active;
}