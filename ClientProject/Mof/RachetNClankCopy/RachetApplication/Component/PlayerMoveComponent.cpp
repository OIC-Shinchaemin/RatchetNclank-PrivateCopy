#include "PlayerMoveComponent.h"

#include "VelocityComponent.h"
#include "MotionStateComponent.h"


void my::PlayerMoveComponent::InputMoveVelocity(float speed) {
    if (auto velocity_com = _velocity_com.lock()) {
        auto accele = Mof::CVector3(0.0f, 0.0f, -speed);
        auto rotate = super::GetOwner()->GetRotate();
        accele.RotateAround(Mof::CVector3(), rotate);

        velocity_com->AddVelocityForce(accele);
    } // if
}

void my::PlayerMoveComponent::InputMoveAngularVelocity(float angle, float speed) {
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

my::PlayerMoveComponent::PlayerMoveComponent(int priority) :
    super(priority),
    _move_speed(0.0f),
    _angular_speed(0.0f),
    _ideal_angle(0.0f),
    _velocity_com(),
    _motion_state_com() {
}

my::PlayerMoveComponent::PlayerMoveComponent(const PlayerMoveComponent& obj) :
    super(obj._priority),
    _move_speed(obj._move_speed),
    _angular_speed(obj._angular_speed),
    _ideal_angle(obj._ideal_angle),
    _velocity_com(),
    _motion_state_com() {
}

my::PlayerMoveComponent::~PlayerMoveComponent() {
}

void my::PlayerMoveComponent::SetMoveSpeed(float speed) {
    this->_move_speed = speed;
}

void my::PlayerMoveComponent::SetAngularSpeed(float speed) {
    this->_angular_speed = speed;
}

void my::PlayerMoveComponent::SetIdealAngle(float radian) {
    this->_ideal_angle = radian;
}

std::string my::PlayerMoveComponent::GetType(void) const {
    return "PlayerMoveComponent";
}

bool my::PlayerMoveComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();

    return true;
}

bool my::PlayerMoveComponent::Update(float delta_time) {
    this->InputMoveAngularVelocity(_ideal_angle, _angular_speed);
    this->InputMoveVelocity(_move_speed);

    super::End();
    return true;
}

bool my::PlayerMoveComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerMoveComponent::Clone(void) {
    return std::make_shared<my::PlayerMoveComponent>(*this);
}

bool my::PlayerMoveComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("PlayerMotionMoveState");
    } // if
    return true;
}