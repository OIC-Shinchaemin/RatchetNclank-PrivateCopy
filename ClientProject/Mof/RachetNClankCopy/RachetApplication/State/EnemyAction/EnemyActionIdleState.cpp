#include "EnemyActionIdleState.h"


state::EnemyActionIdleState::EnemyActionIdleState() :
    super(),
    _idle_com() {
}

state::EnemyActionIdleState::~EnemyActionIdleState() {
}

void state::EnemyActionIdleState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_enemy_com = ptr->GetComponent<my::EnemyComponent>();
    this->_idle_com = ptr->GetComponent<my::EnemyIdleComponent>();
    this->_move_com = ptr->GetComponent<my::EnemyMoveComponent>();
    this->_attack_com = ptr->GetComponent<my::EnemyAttackComponent>();

}

const char* state::EnemyActionIdleState::GetName(void) const {
    return "EnemyActionIdleState";
}

void state::EnemyActionIdleState::Update(float delta_time) {
}

void state::EnemyActionIdleState::Enter(void) {
    float tilt = 1.0f;
    Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);
    auto angle_y = math::ToDegree(super::GetActor()->GetRotate().y);
    in = math::Rotate(in.x, in.y, ut::GenerateRandomF(0.0f, math::kTwoPi));
    float angular_speed = 4.0f;
    
    if (auto idle_com = _idle_com.lock()) {
        idle_com->SetAngularSpeed(angular_speed);
        idle_com->SetIdealAngle(std::atan2(-in.y, in.x) - math::kHalfPi);
        idle_com->Start();
    } // if
    if (auto move_com = _move_com.lock()) {
        move_com->SetMoveSpeed(0.0f);
        move_com->SetAngularSpeed(0.0f);
        move_com->End();
    } // if
}

void state::EnemyActionIdleState::Exit(void) {
}