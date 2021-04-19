#include "EnemyActionMoveState.h"


state::EnemyActionMoveState::EnemyActionMoveState() :
    super() {
}

state::EnemyActionMoveState::~EnemyActionMoveState() {
}

void state::EnemyActionMoveState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_enemy_com = ptr->GetComponent<my::EnemyComponent>();
    this->_idle_com = ptr->GetComponent<my::EnemyIdleComponent>();
    this->_move_com = ptr->GetComponent<my::EnemyMoveComponent>();
    this->_attack_com = ptr->GetComponent<my::EnemyAttackComponent>();
}

const char* state::EnemyActionMoveState::GetName(void) const {
    return "EnemyActionMoveState";
}

void state::EnemyActionMoveState::Update(float delta_time) {
}

void state::EnemyActionMoveState::Enter(void) {
    if (auto move_com = _move_com.lock()) {
        auto target = _enemy_com.lock()->GetTarget().lock()->GetPosition();
        float speed = 0.2f;
        float angular_speed = 1.0f;

        float tilt = 1.0f;
        Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);
        auto dir = target - super::GetActor()->GetPosition();
        float angle = std::atan2(dir.z, dir.x);
        in = math::Rotate(in.x, in.y, angle);

        move_com->SetMoveSpeed(speed);
        move_com->SetAngularSpeed(angular_speed);
        move_com->SetIdealAngle(std::atan2(-in.y, in.x) - math::kHalfPi);
        move_com->Start();
    } // if
    if (auto attack_com = _attack_com.lock()) {
        attack_com->End();
    } // if
}

void state::EnemyActionMoveState::Exit(void) {
}