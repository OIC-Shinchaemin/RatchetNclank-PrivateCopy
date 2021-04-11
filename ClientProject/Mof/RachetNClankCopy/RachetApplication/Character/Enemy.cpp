#include "Enemy.h"

#include "Player.h"
#include "../Collision/Object/EnemyCollisionObject.h"
#include "../Collision/Object/EnemySightCollisionObject.h"
#include "../State/AIPatrolState.h"
#include "../State/AICombatState.h"
#include "../Component/IdleComponent.h"
#include "../Component/MoveComponent.h"
#include "../Component/AttackComponent.h"


void my::Enemy::ChaseTo(Mof::CVector3 target, float speed, float angular_speed) {
    auto move_com = super::GetComponent<my::MoveComponent>();

    float tilt = 1.0f;
    Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);

    auto dir = target - super::GetPosition();
    float angle = std::atan2(dir.z, dir.x);
    in = math::Rotate(in.x, in.y, angle);

    move_com->SetMoveSpeed(speed);
    move_com->SetAngularSpeed(angular_speed);
    move_com->SetIdealAngle(std::atan2(-in.y, in.x) - math::kHalfPi);
    move_com->Start();
}

float my::Enemy::GetDistanceFromInitPosition(void) {
    return Mof::CVector3Utilities::Distance(_init_position, super::GetPosition());
}

bool my::Enemy::HasTarget(void) {
    return !_target.expired();
}

bool my::Enemy::TargetInAttackRange(void) {
    if (auto target = _target.lock()) {
        auto attack_com = super::GetComponent<my::AttackComponent>();
        if (attack_com->GetCanAttackRangeSphere().CollisionPoint(target->GetPosition())) {
            return true;
        } // if
    } // if
    return false;
}

bool my::Enemy::GoHome(void) {
    this->ChaseTo(_init_position, 0.3f, 1.0f);

    if (this->GetDistanceFromInitPosition() > 2.0f) {
        return false;
    } // if
    return true;
}

bool my::Enemy::OverLooking(void) {
    if (this->HasTarget()) {
        _ai_state_machine.ChangeState("AICombatState");
        return true;
    } // if

    auto idle_com = super::GetComponent<my::IdleComponent>();

    float tilt = 1.0f;
    Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);

    auto angle_y = math::ToDegree(super::GetRotate().y);

    in = math::Rotate(in.x, in.y, ut::GenerateRandomF(0.0f, math::kTwoPi));
    float angular_speed = 4.0f;

    // _overlooking.Action();
    idle_com->SetAngularSpeed(angular_speed);
    idle_com->SetIdealAngle(std::atan2(-in.y, in.x) - math::kHalfPi);
    idle_com->Start();
    return false;
}

bool my::Enemy::ChaseTarget(void) {
    if (auto target = _target.lock()) {
        if (this->TargetInAttackRange()) {
            return true;
        } // if
        this->ChaseTo(target->GetPosition(), 0.2f, 1.0f);
        return false;
    } // if
    return true;
}

bool my::Enemy::Attack(void) {
    auto move_com = super::GetComponent<my::MoveComponent>();

    move_com->SetMoveSpeed(0.0f);
    move_com->SetAngularSpeed(0.0f);

    auto attack_com = super::GetComponent<my::AttackComponent>();

    attack_com->Start();
    _ai_state_machine.ChangeState("AICombatState");
    return false;
}

void my::Enemy::RenderRay(const Mof::CRay3D& ray, float length, int color) {
    ::CGraphicsUtilities::RenderLine(ray.Position,
                                     ray.Position + ray.Direction * length,
                                     color);
}

void my::Enemy::RenderRay(Mof::Vector3 start, float degree_y) {
    auto ray = Mof::CRay3D(start);
    auto rotate = super::GetRotate();
    rotate.y += math::ToRadian(degree_y);

    Mof::CMatrix44 mat;
    mat.RotationZXY(rotate);
    ray.Direction = -math::vec3::kUnitZ * mat;

    this->RenderRay(ray, _sight->GetRange(), def::color_rgba_u32::kGreen);
}

my::Enemy::Enemy() :
    super(),
    _init_position(),
    _target(),
    _sight(),
    _thinking_time() {
    super::_motion_names = my::ResourceLocator::GetResource<my::MotionNames>("../Resource/motion_names/enemy.motion_names");
}

my::Enemy::~Enemy() {
}

void my::Enemy::SetTarget(const std::shared_ptr<my::Character>& ptr) {
    this->_target = ptr;
}

void my::Enemy::GenerateCollisionObject(void) {
    auto coll = std::make_shared<my::EnemyCollisionObject>();
    coll->SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));
    super::AddCollisionObject(coll);
    coll->AddCollisionFunc(my::CollisionObject::CollisionFuncType::Enter,
                           "PlayerCollisionObject",
                           my::CollisionObject::CollisionFunc([&](const my::CollisionInfo& in) {
        this->End(); return true;
    }));

    auto sight_coll = std::make_shared<my::EnemySightCollisionObject>();
    sight_coll->SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));
    sight_coll->SetSight(_sight);
    super::AddCollisionObject(sight_coll);
    sight_coll->AddCollisionFunc(my::CollisionObject::CollisionFuncType::Enter,
                                 "PlayerCollisionObject",
                                 my::CollisionObject::CollisionFunc([&](const my::CollisionInfo& in) {
        auto target = std::any_cast<std::weak_ptr<Player>>(in.target);
        if (auto ptr = target.lock()) {
            this->SetTarget(ptr);
        } // if
        return true;
    }));
    sight_coll->AddCollisionFunc(my::CollisionObject::CollisionFuncType::Exit,
                                 "PlayerCollisionObject",
                                 my::CollisionObject::CollisionFunc([&](const my::CollisionInfo& in) {
        this->SetTarget(nullptr);
        return true;
    }));
}

bool my::Enemy::Initialize(my::Actor::Param* param) {
    super::Initialize(param);
    _init_position = super::GetPosition();
    _thinking_time.Initialize(0.0f, true);
    // generate
    //_idle = std::make_shared<my::Idle>();
    //_move = std::make_shared<my::Move>();
    _sight = std::make_shared<my::SightRecognition>();
    this->GenerateCollisionObject();

    _sight->SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));

    // state
    this->RegisterAIState<state::AIPatrolState>(_ai_state_machine);
    this->RegisterAIState<state::AICombatState>(_ai_state_machine);
    _ai_state_machine.ChangeState("AIPatrolState");
    return true;
}

bool my::Enemy::Input(void) {
    float delta_time = 1.0f / 60.0f;
    if (_thinking_time.Tick(delta_time)) {
        _ai_state_machine.Update(delta_time);
    } // if
    return true;
}

bool my::Enemy::Update(float delta_time) {
    my::Actor::Update(delta_time);
    return true;
}

bool my::Enemy::Render(void) {
    my::Actor::Render();
    return true;
}

bool my::Enemy::ChangeToPatrolState(void) {
    _ai_state_machine.ChangeState("AIPatrolState");
    return true;
}

bool my::Enemy::ChangeToCombatState(void) {
    _ai_state_machine.ChangeState("AICombatState");
    return true;
}

void my::Enemy::RenderDebug(void) {
    super::RenderDebug();

    // Ž‹ü•`‰æ
    Mof::Vector3 start = super::GetPosition();
    float h = super::_height;
    start.y += h;

    // Ž‹ŠE‹«ŠE•\Ž¦
    this->RenderRay(start, 0.0f);
    this->RenderRay(start, 90.0f);
    this->RenderRay(start, -90.0f);

    // ‘ÎÛ‚Ö‚ÌŽ‹ü‚ð•\Ž¦
    if (auto target = _target.lock()) {
        auto pos = target->GetPosition();
        pos.y += super::_height;
        auto diff = pos - start;
        auto ray = Mof::CRay3D(start, diff);
        this->RenderRay(ray, Mof::CVector3Utilities::Length(diff), def::color_rgba_u32::kYellow);
    } // if    

    _ai_state_machine.DebugRender();
    ::CGraphicsUtilities::RenderString(0.0f, 0.0f, "state = %s", _ai_state_machine.GetCurrentStateName());
}