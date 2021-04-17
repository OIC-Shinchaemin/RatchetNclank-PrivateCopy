#include "Enemy.h"

#include "Player.h"
#include "../Collision/Object/EnemyCollisionObject.h"
#include "../Collision/Object/EnemySightCollisionObject.h"
#include "../State/EnemyMotionIdleState.h"
#include "../State/EnemyMotionMoveState.h"
#include "../State/EnemyMotionAttackState.h"
#include "../State/AIPatrolState.h"
#include "../State/AICombatState.h"


void my::Enemy::ChaseTo(Mof::CVector3 target, float speed, float angular_speed) {
    float tilt = 1.0f;
    Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);

    auto dir = target - super::GetPosition();
    float angle = std::atan2(dir.z, dir.x);
    in = math::Rotate(in.x, in.y, angle);

    _move->SetMoveSpeed(speed);
    _move->SetAngularSpeed(angular_speed);
    _move->SetIdealAngle(std::atan2(-in.y, in.x) - math::kHalfPi);
    _move->Start();
}

float my::Enemy::GetDistanceFromInitPosition(void) {
    return Mof::CVector3Utilities::Distance(_init_position, super::GetPosition());
}

bool my::Enemy::HasTarget(void) {
    return !_target.expired();
}

bool my::Enemy::TargetInAttackRange(void) {
    if (auto target = _target.lock()) {
        if (_attack->GetCanAttackRangeSphere().CollisionPoint(target->GetPosition())) {
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
    float tilt = 1.0f;
    Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);

    auto angle_y = math::ToDegree(super::GetRotate().y);

    in = math::Rotate(in.x, in.y, ut::GenerateRandomF(0.0f, math::kTwoPi));
    float angular_speed = 4.0f;

    // _overlooking.Action();
    _idle->SetAngularSpeed(angular_speed);
    _idle->SetIdealAngle(std::atan2(-in.y, in.x) - math::kHalfPi);
    _idle->Start();
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
    _attack->Start();
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
    _idle(),
    _move(),
    _sight(),
    _attack(),
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
    _idle = std::make_shared<my::Idle>();
    _move = std::make_shared<my::Move>();
    _sight = std::make_shared<my::SightRecognition>();
    _attack = std::make_shared<my::Attack>();
    this->GenerateCollisionObject();

    /*
    // mesh motion
    if (auto mesh = _mesh.lock()) {
        _motion = mesh->CreateMotionController();
    } // if
    if (auto motion_names = super::_motion_names.lock();  !super::_motion_names.expired() && _motion) {
        _motion->ChangeMotionByName(motion_names->GetName(MotionType::IdleWait), 1.0f, true);
    } // if
    for (int i = 0; i < _motion->GetMotionCount(); i++) {
        std::cout << "_motion->GetMotion(i)->GetName()" << _motion->GetMotion(i)->GetName()->GetString() << "\n";
    } // for
    */

    // components initialize
    _idle->SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));
    _move->SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));
    _sight->SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));
    _attack->SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));
    _idle->SetVelocity(&_velocity);
    _move->SetVelocity(&_velocity);
    _attack->SetMotion(_motion);

    // state
    /*
    this->RegisterMotionState<state::EnemyMotionIdleState>(_motion_state_machine);
    this->RegisterMotionState<state::EnemyMotionMoveState>(_motion_state_machine);
    this->RegisterMotionState<state::EnemyMotionAttackState>(_motion_state_machine);
    _motion_state_machine.ChangeState("EnemyMotionIdleState");
    */
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
    //_motion->AddTimer(delta_time);

    if (_idle->IsActive()) {
        _idle->Update(delta_time);
    } // if
    if (_move->IsActive()) {
        _move->Update(delta_time);
    } // if
    if (_attack->IsActive()) {
        _attack->Update(delta_time);
    } // if

    _velocity.Update(delta_time);

//    super::Update(delta_time);
    //_motion_state_machine.Update(delta_time);

    super::UpdateTransform(delta_time);

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
bool my::Enemy::ChangeMotionState(const char* next) {
    //_motion_state_machine.ChangeState(next);
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
    _attack->RenderDebug();

    _ai_state_machine.DebugRender();
    //_motion_state_machine.DebugRender();
    ::CGraphicsUtilities::RenderString(0.0f, 0.0f, "state = %s", _ai_state_machine.GetCurrentStateName());
    //::CGraphicsUtilities::RenderString(0.0f, 0.0f, "state = %s", _motion_state_machine.GetCurrentStateName());
}