#include "EnemyActionGoHomeState.h"


state::EnemyActionGoHomeState::EnemyActionGoHomeState() :
    super() {
}

state::EnemyActionGoHomeState::~EnemyActionGoHomeState() {
}

void state::EnemyActionGoHomeState::SetActor(const std::shared_ptr<my::Actor>& ptr) {
    super::SetActor(ptr);
    this->_enemy_com = ptr->GetComponent<my::EnemyComponent>();
    this->_idle_com = ptr->GetComponent<my::EnemyIdleComponent>();
    this->_move_com = ptr->GetComponent<my::EnemyMoveComponent>();
    this->_attack_com = ptr->GetComponent<my::EnemyMeleeAttackComponent>();
}

const char* state::EnemyActionGoHomeState::GetName(void) const {
    return "EnemyActionGoHomeState";
}

void state::EnemyActionGoHomeState::Update(float delta_time) {
}

void state::EnemyActionGoHomeState::Enter(void) {
    if (auto move_com = _move_com.lock()) {
        move_com->Start();

        Mof::CVector3 target = super::GetActor()->GetInitialPosition();
        float speed = 0.3f;
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

void state::EnemyActionGoHomeState::Exit(void) {
}