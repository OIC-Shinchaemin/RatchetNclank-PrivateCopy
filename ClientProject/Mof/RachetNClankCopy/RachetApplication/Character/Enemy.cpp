#include "Enemy.h"


bool my::Enemy::ChangeToMoveState(void) {
    _enemy_state = my::EnemyState::Move;
    return true;
}

bool my::Enemy::ChangeToAttackState(void) {
    _enemy_state = my::EnemyState::Attack;
    return true;
}

bool my::Enemy::ChangeToPatrolState(void) {
    _state = my::AIState::Patrol;
    _patrol_behaviour_executor->Reset();
    return true;
}

bool my::Enemy::ChangeToCombatState(void) {
    _state = my::AIState::Combat;
    _combat_behaviour_executor->Reset();
    return true;
}

float my::Enemy::GetDistanceFromInitPosition(void) {
    return Mof::CVector3Utilities::Distance(_init_position, super::GetPosition());
}

bool my::Enemy::HasTarget(void) {
    return !_target.expired();
}

bool my::Enemy::TargetInAttackRange(void) {
    if (auto target = _target.lock()) {
        if (_attack.GetRangeSphere().CollisionPoint(target->GetPosition())) {
            return true;
        } // if
    } // if
    return false;
}

bool my::Enemy::OverLooking(void) {
    if (this->HasTarget()) {
        this->ChangeToCombatState();
        return true;
    } // if

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
    _attack.Start();
    _combat_behaviour_executor->Reset();
    return false;
}

void my::Enemy::ChaseTo(Mof::CVector3 target, float speed, float angular_speed) {
    _enemy_state = my::EnemyState::Move;


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

    this->RenderRay(ray, _sight.GetRange(), def::color_rgba_u32::kGreen);
}

my::Enemy::Enemy() :
    super(),
    _init_position(),
    _target(),
    _sight(),
    _attack(),
    _state(my::AIState::Patrol),
    _enemy_state(my::EnemyState::Move),
    _patrol_behaviour_executor(),
    _combat_behaviour_executor() {
    super::_mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/Chara/Chr_01_ion_mdl_01.mom");
    float scale = 0.2f;
    super::SetScale(Mof::CVector3(scale, scale, scale));
}

my::Enemy::~Enemy() {
}

void my::Enemy::SetTarget(const std::shared_ptr<my::Character>& ptr) {
    this->_target = ptr;
}

Mof::CSphere my::Enemy::GetAttackSphere(void) const {
    return  this->_attack.GetSphere();
}

bool my::Enemy::Initialize(const def::Transform& transform) {
    super::Initialize(transform);
    //_init_position = super::GetPosition();
    _init_position = Mof::CVector3(5.0f, 0.0f, 5.0f);
    _sight.SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));
    _attack.SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));

    _combat_behaviour_executor =  _behaviour_executor_factory.Create("../Resource/behaviour/combat.json");
    _patrol_behaviour_executor = _behaviour_executor_factory.Create("../Resource/behaviour/patrol.json");

    if (auto mesh = _mesh.lock()) {
        _motion = mesh->CreateMotionController();
        _motion->ChangeMotion(0);
    } // if
    return true;
}

bool my::Enemy::Input(void) {
    // å„Ç…Ç…EnemyStateÇÃÉÅÉìÉoÇ…éùÇΩÇπÇÈ
    auto temp = std::dynamic_pointer_cast<my::Enemy>(shared_from_this());

    if (_state == my::AIState::Patrol) {
        _patrol_behaviour_executor->Execute(temp);
    } // if
    else if (_state == my::AIState::Combat) {
        _combat_behaviour_executor->Execute((temp));
    } // else if
    return true;
}

bool my::Enemy::Update(float delta_time) {
    super::Update(delta_time);
    super::UpdateTransform(delta_time);
    return true;
}

bool my::Enemy::Render(void) {
    super::Render();
    return true;
}

bool my::Enemy::ContainInRecognitionRange(Mof::CVector3 pos) {
    return _sight.ContainInRecognitionRange(pos);
}

void my::Enemy::RenderDebug(void) {
    super::RenderDebug();

    // éãê¸ï`âÊ
    Mof::Vector3 start = super::GetPosition();
    float h = super::_height;
    start.y += h;

    // éãäEã´äEï\é¶
    this->RenderRay(start, 0.0f);
    this->RenderRay(start, 90.0f);
    this->RenderRay(start, -90.0f);

    // ëŒè€Ç÷ÇÃéãê¸Çï\é¶
    if (auto target = _target.lock()) {
        auto pos = target->GetPosition();
        pos.y += super::_height;
        auto diff = pos - start;
        auto ray = Mof::CRay3D(start, diff);
        this->RenderRay(ray, Mof::CVector3Utilities::Length(diff), def::color_rgba_u32::kYellow);
    } // if


    if (_state == my::AIState::Patrol) {
        ::CGraphicsUtilities::RenderString(0.0f, 0.0f, "state = Patrol");
        _patrol_behaviour_executor->DebugRender();
    } // if
    else if (_state == my::AIState::Combat) {
        ::CGraphicsUtilities::RenderString(0.0f, 0.0f, "state = Combat");
        _combat_behaviour_executor->DebugRender();
    } // else if

    if (_enemy_state == my::EnemyState::Move) {
        ::CGraphicsUtilities::RenderString(0.0f, 20.0f, "state = Move");
    } // if
    else if (_enemy_state == my::EnemyState::Attack) {
        ::CGraphicsUtilities::RenderString(0.0f, 20.0f, "state = Attack");
    } // else if
    _attack.RenderDebug();
}