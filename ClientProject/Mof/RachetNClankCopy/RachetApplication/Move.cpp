#include "Move.h"

#include "My/Core/Math.h"
#include "Character/Enemy.h"


void my::Move::InputMoveVelocity(float speed) {
    auto accele = Mof::CVector3(0.0f, 0.0f, -speed);
    auto rotate = super::GetOwner()->GetRotate();
    accele.RotateAround(Mof::CVector3(), rotate);

    _velocity->AddVelocityForce(accele);
}

void my::Move::InputMoveVelocity(Mof::CVector2 stick, float speed) {
    // ì¸óÕë¨ìx
    this->InputMoveVelocity(speed * stick.Length());
}

void my::Move::InputMoveAngularVelocity(Mof::CVector2 stick, float speed) {
    // ì¸óÕäpìx
    float angle_y = std::atan2(-stick.y, stick.x) - math::kHalfPi;
    this->InputMoveAngularVelocity(angle_y, speed);
}

void my::Move::InputMoveAngularVelocity(float angle, float speed) {
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

bool my::Move::InactiveCondition(void) const {
    return true;
}

void my::Move::Execute(float delta_time) {
    this->InputMoveAngularVelocity(_ideal_angle, _angular_speed);
    this->InputMoveVelocity(_move_speed);
}

my::Move::Move() :
    super(),
    _move_speed(0.0f),
    _angular_speed(0.0f),
    _ideal_angle(0.0f),
    _velocity() {
}

my::Move::~Move() {
}

void my::Move::SetVelocity(my::Velocity* ptr) {
    this->_velocity = ptr;
}

void my::Move::SetMoveSpeed(float speed) {
    this->_move_speed = speed;
}

void my::Move::SetAngularSpeed(float speed) {
    this->_angular_speed = speed;
}

void my::Move::SetIdealAngle(float radian) {
    this->_ideal_angle = radian;
}

bool my::Move::Start(void) {
    if (_active) {
        return false;
        puts("sdg");
    } // if
    _active = true;
    super::GetOwner()->ChangeMotionState("EnemyMotionMoveState");
    return _active;
}