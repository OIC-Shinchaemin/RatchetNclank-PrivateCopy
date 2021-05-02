#include "EnemyActionIdleState.h"


state::EnemyActionIdleState::EnemyActionIdleState() :
    super(),
    _enemy_com(),
    _idle_com(),
    _move_com(),
    _melee_attack_com(),
    _ranged_attack_com(),
    _damage_com() {
}

state::EnemyActionIdleState::~EnemyActionIdleState() {
}

void state::EnemyActionIdleState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_enemy_com = ptr->GetComponent<my::EnemyComponent>();
    this->_idle_com = ptr->GetComponent<my::EnemyIdleComponent>();
    this->_move_com = ptr->GetComponent<my::EnemyMoveComponent>();
    this->_melee_attack_com = ptr->GetComponent<my::EnemyMeleeAttackComponent>();
    this->_ranged_attack_com = ptr->GetComponent<my::EnemyRangedAttackComponent>();
    this->_damage_com = ptr->GetComponent<my::EnemyDamageComponent>();
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
        float angle = idle_com->GetIdealAngle();
        angle += math::ToRadian(0.5f);
        if (math::ToRadian(360.0f) < angle) {
            angle = 0.0f;
        } // if
        idle_com->SetIdealAngle(angle);
        idle_com->Start();
    } // if
    if (auto move_com = _move_com.lock()) {
        move_com->SetMoveSpeed(0.0f);
        move_com->SetAngularSpeed(0.0f);
        move_com->End();
    } // if
    if (auto melee_attack_com = _melee_attack_com.lock()) {
        melee_attack_com->End();
    } // if
    if (auto ranged_attack_com = _ranged_attack_com.lock()) {
        ranged_attack_com->End();
    } // if
}

void state::EnemyActionIdleState::Exit(void) {
    if (auto idle_com = _idle_com.lock()) {
        //idle_com->End();
    } // if
}