#include "EnemyMoveComponent.h"

#include "../VelocityComponent.h"
#include "EnemyStateComponent.h"
#include "../MotionStateComponent.h"
#include "EnemyComponent.h"
#include "../../State/EnemyActionStateDefine.h"
#include "../../State/EnemyMotionStateDefine.h"


void ratchet::component::enemy::EnemyMoveComponent::InputMoveVelocity(float speed) {
    if (auto velocity_com = _velocity_com.lock()) {
        auto accele = Mof::CVector3(0.0f, 0.0f, -speed);
        auto rotate = super::GetOwner()->GetRotate();
        accele.RotateAround(Mof::CVector3(), rotate);

        velocity_com->AddVelocityForce(accele);
    } // if
}

void ratchet::component::enemy::EnemyMoveComponent::InputMoveAngularVelocity(float angle, float speed) {
    if (auto velocity_com = _velocity_com.lock()) {

        float angle_y = angle;
        if (math::kTwoPi <= angle_y) {
            angle_y -= math::kTwoPi;
        } // if
        else if (angle_y <= 0.0f) {
            angle_y += math::kTwoPi;
        } // else if

        auto rotate = super::GetOwner()->GetRotate();
        // ?????p?x
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

ratchet::component::enemy::EnemyMoveComponent::EnemyMoveComponent(int priority) :
    super(priority),
    _move_speed(0.0f),
    _angular_speed(0.0f),
    _ideal_angle(0.0f),
    _target(),
    _velocity_com(),
    _motion_state_com() {
}

ratchet::component::enemy::EnemyMoveComponent::EnemyMoveComponent(const EnemyMoveComponent& obj) :
    super(obj),
    _move_speed(obj._move_speed),
    _angular_speed(obj._angular_speed),
    _ideal_angle(obj._ideal_angle),
    _target(),
    _velocity_com(),
    _motion_state_com() {
}

ratchet::component::enemy::EnemyMoveComponent::~EnemyMoveComponent() {
}

void ratchet::component::enemy::EnemyMoveComponent::SetMoveSpeed(float speed) {
    this->_move_speed = speed;
}

void ratchet::component::enemy::EnemyMoveComponent::SetAngularSpeed(float speed) {
    this->_angular_speed = speed;
}

void ratchet::component::enemy::EnemyMoveComponent::SetIdealAngle(float radian) {
    this->_ideal_angle = radian;
}

void ratchet::component::enemy::EnemyMoveComponent::SetTargetPosition(Mof::CVector3 position) {
    this->_target = position;
}

std::string ratchet::component::enemy::EnemyMoveComponent::GetType(void) const {
    return "EnemyMoveComponent";
}

std::string_view ratchet::component::enemy::EnemyMoveComponent::GetStateType(void) const {
    return state::EnemyActionStateType::kEnemyActionMoveState;
}

Mof::CVector3 ratchet::component::enemy::EnemyMoveComponent::GetTargetPosition(void) const {
    return this->_target;
}

bool ratchet::component::enemy::EnemyMoveComponent::Initialize(void) {
    super::Initialize();

    _velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    _action_state_com = super::GetOwner()->GetComponent<ratchet::component::enemy::EnemyStateComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<ratchet::component::MotionStateComponent>();
    _ENEMY_com = super::GetOwner()->GetComponent<ratchet::component::enemy::EnemyComponent>();
    return true;
}

bool ratchet::component::enemy::EnemyMoveComponent::Update(float delta_time) {
    if (auto ENEMY_com = _ENEMY_com.lock()) {
        if (auto target = ENEMY_com->GetTarget().lock()) {
            _target = target->GetPosition();
        } // if
    } // if

    float speed = 1.0f;
    float angular_speed = 1.0f;

    float tilt = 1.0f;
    Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);
    auto dir = _target - super::GetOwner()->GetPosition();
    float angle = std::atan2(dir.z, dir.x);
    in = math::Rotate(in.x, in.y, angle);

    this->SetMoveSpeed(speed);
    this->SetAngularSpeed(angular_speed);
    this->SetIdealAngle(std::atan2(-in.y, in.x) - math::kHalfPi);

    //

    this->InputMoveAngularVelocity(_ideal_angle, _angular_speed);
    this->InputMoveVelocity(_move_speed);


    return true;
}

bool ratchet::component::enemy::EnemyMoveComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::enemy::EnemyMoveComponent::Clone(void) {
    return std::make_shared<ratchet::component::enemy::EnemyMoveComponent>(*this);
}

bool ratchet::component::enemy::EnemyMoveComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState(state::EnemyMotionStateType::kEnemyMotionMoveState);
    } // if
    return true;
}