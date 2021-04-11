#include "MoveComponent.h"

#include "VelocityComponent.h"
#include "MotionStateComponent.h"


void my::MoveComponent::InputMoveVelocity(float speed) {
    if (auto velocity_com = _velocity_com.lock()) {
        auto accele = Mof::CVector3(0.0f, 0.0f, -speed);
        auto rotate = super::GetOwner()->GetRotate();
        accele.RotateAround(Mof::CVector3(), rotate);

        velocity_com->AddVelocityForce(accele);
    } // if
}

void my::MoveComponent::InputMoveAngularVelocity(float angle, float speed) {
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

my::MoveComponent::MoveComponent(int priority) :
    super(priority),
    _move_speed(0.0f),
    _angular_speed(0.0f),
    _ideal_angle(0.0f),
    _velocity_com(),
    _motion_state_com() {
}

my::MoveComponent::MoveComponent(const MoveComponent& obj) :
    super(obj._priority),
    _move_speed(obj._move_speed),
    _angular_speed(obj._angular_speed),
    _ideal_angle(obj._ideal_angle),
    _velocity_com(),
    _motion_state_com() {
}

my::MoveComponent::~MoveComponent() {
}

void my::MoveComponent::SetMoveSpeed(float speed) {
    this->_move_speed = speed;
}

void my::MoveComponent::SetAngularSpeed(float speed) {
    this->_angular_speed = speed;
}

void my::MoveComponent::SetIdealAngle(float radian) {
    this->_ideal_angle = radian;
}

std::string my::MoveComponent::GetType(void) const {
    return "MoveComponent";
}

bool my::MoveComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();

    return true;
}

bool my::MoveComponent::Update(float delta_time) {
    this->InputMoveAngularVelocity(_ideal_angle, _angular_speed);
    this->InputMoveVelocity(_move_speed);

    super::End();
    return true;
}

bool my::MoveComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::MoveComponent::Clone(void) {
    return std::make_shared<my::MoveComponent>(*this);
}

bool my::MoveComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("EnemyMotionMoveState");
    } // if
    return true;
}