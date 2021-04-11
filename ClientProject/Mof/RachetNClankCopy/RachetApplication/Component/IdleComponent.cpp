#include "IdleComponent.h"

#include "VelocityComponent.h"
#include "MotionStateComponent.h"



void my::IdleComponent::InputMoveAngularVelocity(float angle, float speed) {
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

my::IdleComponent::IdleComponent(int priority) :
    super(priority),
    _angular_speed(0.0f),
    _ideal_angle(0.0f),
    _velocity_com(),
    _motion_state_com() {
}

my::IdleComponent::IdleComponent(const IdleComponent& obj) :
    super(obj._priority),
    _angular_speed(obj._angular_speed),
    _ideal_angle(obj._ideal_angle),
    _velocity_com(),
    _motion_state_com() {
}

my::IdleComponent::~IdleComponent() {
}

void my::IdleComponent::SetAngularSpeed(float speed) {
    this->_angular_speed = speed;
}

void my::IdleComponent::SetIdealAngle(float radian) {
    this->_ideal_angle = radian;
}

std::string my::IdleComponent::GetType(void) const {
    return "IdleComponent";
}

bool my::IdleComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();
    return true;
}

bool my::IdleComponent::Update(float delta_time) {
    this->InputMoveAngularVelocity(_ideal_angle, _angular_speed);
    super::End();
    return true;
}

bool my::IdleComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::IdleComponent::Clone(void) {
    return std::make_shared<my::IdleComponent>(*this);
}

bool my::IdleComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("EnemyMotionIdleState");
    } // if
    return true;
}