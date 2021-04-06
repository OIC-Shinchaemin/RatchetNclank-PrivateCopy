#include "Enemy.h"

#include "Player.h"
#include "../Collision/Object/EnemyCollisionObject.h"
#include "../Collision/Object/EnemySightCollisionObject.h"
#include "../State/EnemyMotionIdleState.h"
#include "../State/EnemyMotionMoveState.h"
#include "../State/EnemyMotionAttackState.h"
#include "../State/AIPatrolState.h"
#include "../State/AICombatState.h"


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

bool my::Enemy::OverLooking(void) {
    if (this->HasTarget()) {
        _ai_state_machine.ChangeState("AICombatState");
        this->ChangeToCombatState();
        return true;
    } // if

    // _overlooking.Action();

    float tilt = 1.0f;
    Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);

    auto angle_y = math::ToDegree(super::GetRotate().y);

    in = math::Rotate(in.x, in.y, ut::GenerateRandomF(0.0f, math::kTwoPi));
    float angular_speed = 4.0f;
    this->InputMoveAngularVelocity(in, angular_speed);
    return false;
}

bool my::Enemy::GoHome(void) {
    this->ChaseTo(_init_position, 0.3f, 1.0f);
    if (this->GetDistanceFromInitPosition() > 2.0f) {
        return false;
    } // if
    return true;
}

bool my::Enemy::Attack(void) {
    _attack->Start();
    _ai_state_machine.ChangeState("AICombatState");
    return false;
//    return _attack->IsActive();
}

void my::Enemy::ChaseTo(Mof::CVector3 target, float speed, float angular_speed) {
//    _enemy_state = my::EnemyState::Move;


    float tilt = 1.0f;
    Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);

    auto dir = target - super::GetPosition();
    float angle = std::atan2(dir.z, dir.x);
    in = math::Rotate(in.x, in.y, angle);

    this->InputMoveAngularVelocity(in, angular_speed);
    this->InputMoveVelocity(in, speed);
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
    _attack()
 //   ,
 //  _enemy_state(my::EnemyState::Move) 

{
    super::_mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/Chara/Chr_01_ion_mdl_01.mom");
    super::_motion_names = my::ResourceLocator::GetResource<my::MotionNames>("../Resource/motion_names/enemy.motion_names");
    float scale = 0.2f;
    super::SetScale(Mof::CVector3(scale, scale, scale));
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
    _sight = std::make_shared<my::SightRecognition>();
    _attack = std::make_shared<my::Attack>();
    this->GenerateCollisionObject();

    // components initialize
    _init_position = super::GetPosition();
    _sight->SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));
    _attack->SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));

    // mesh motion
    if (auto mesh = _mesh.lock()) {
        _motion = mesh->CreateMotionController();
    } // if
    if (_motion) {
        if (auto motion_names = super::_motion_names.lock()) {
            _motion->ChangeMotionByName(motion_names->GetName(MotionType::IdleWait), 1.0f, true);
        } // if
    } // if

    // state
    this->RegisterMotionState<state::EnemyMotionIdleState>(_motion_state_machine);
    this->RegisterMotionState<state::EnemyMotionMoveState>(_motion_state_machine);
    this->RegisterMotionState<state::EnemyMotionAttackState>(_motion_state_machine);
    _motion_state_machine.ChangeState("EnemyMotionIdleState");
    this->RegisterAIState<state::AIPatrolState>(_ai_state_machine);
    this->RegisterAIState<state::AICombatState>(_ai_state_machine);
    _ai_state_machine.ChangeState("AIPatrolState");
    return true;
}

bool my::Enemy::Input(void) {
    _ai_state_machine.Update(1.0f / 60.0f);
    return true;
}

bool my::Enemy::Update(float delta_time) {
    super::Update(delta_time);
    _motion_state_machine.Update(delta_time);
    super::UpdateTransform(delta_time);
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
    _motion_state_machine.ChangeState(next);
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
    _motion_state_machine.DebugRender();
    ::CGraphicsUtilities::RenderString(0.0f, 0.0f, "state = %s", _ai_state_machine.GetCurrentStateName());
    ::CGraphicsUtilities::RenderString(0.0f, 0.0f, "state = %s", _motion_state_machine.GetCurrentStateName());
}