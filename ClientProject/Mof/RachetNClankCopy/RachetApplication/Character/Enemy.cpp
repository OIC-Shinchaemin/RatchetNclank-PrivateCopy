#include "Enemy.h"

<<<<<<< HEAD
#include "Player.h"
#include "../Collision/Object/EnemyCollisionObject.h"
#include "../Collision/Object/EnemySightCollisionObject.h"

<<<<<<< HEAD
=======

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
=======
#include "../Behaviour/Node/Node.h"
#include "../Behaviour/Node/SequencerNode.h"
#include "../Behaviour/Node/SelectorNode.h"
#include "../Behaviour/Node/ActionNode.h"
#include "../Behaviour/Node/ConditionalNode.h"
#include "../Behaviour/Node/DecoratorNode.h"
#include "../Behaviour/Node/ParameterNode.h"


//using BehaviourActor = my::Actor;
// 外部から受け取る
behaviour::CompositeNodePtr< std::shared_ptr<my::Enemy> > _patrol_rootnode;
behaviour::CompositeNodePtr< std::shared_ptr<my::Enemy> > _combat_rootnode;

behaviour::NodeExecutorPtr<my::Enemy::EnemyPtr> my::Enemy::CreatePatrolBehaviour(void) {
    using namespace behaviour;
    _patrol_rootnode = std::make_shared<SelectorNode<EnemyPtr>>();
    
    auto decorator_0 = std::make_shared < DecoratorNode<EnemyPtr, float>>(
        ConditionalNodeBase< EnemyPtr>::Operator::GreaterEqual,
        std::make_shared<GetNode<EnemyPtr, float>>(&Enemy::GetDistanceFromInitPosition),
        std::make_shared<ValueNode<EnemyPtr, float>>(2.0f));

    auto action_0 = std::make_shared<behaviour::FunctionNode<EnemyPtr>>(&my::Enemy::GoHome);
    decorator_0->SetChild(action_0);
    

    auto action_1 = std::make_shared<behaviour::FunctionNode<EnemyPtr>>(&my::Enemy::OverLooking);
    _patrol_rootnode->AddChild(decorator_0);
    _patrol_rootnode->AddChild(action_1);
    return _patrol_rootnode->CreateExecutor();
}
behaviour::NodeExecutorPtr<my::Enemy::EnemyPtr> my::Enemy::CreateCombatBehaviour(void) {
    _combat_rootnode = std::make_shared< behaviour::SelectorNode< my::Enemy::EnemyPtr>>();
    auto action_0 = std::make_shared<behaviour::FunctionNode<my::Enemy::EnemyPtr>>(&my::Enemy::Chase);
    _combat_rootnode->AddChild(action_0);
    return _combat_rootnode->CreateExecutor();
}

float my::Enemy::GetDistanceFromInitPosition(void) const {
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    return Mof::CVector3Utilities::Distance(_init_position, super::GetPosition());
}

bool my::Enemy::HasTarget(void) {
    return !_target.expired();
}

bool my::Enemy::TargetInAttackRange(void) {
    if (auto target = _target.lock()) {
        if (_attack->GetRangeSphere().CollisionPoint(target->GetPosition())) {
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
    _attack->Start();
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

<<<<<<< HEAD
>>>>>>> origin/Ex55_WeaponAction
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
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
<<<<<<< HEAD
<<<<<<< HEAD
    _state(my::AIState::Patrol) {
=======
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    _init_position(),
    _target(),
    _sight(),
    _attack(),
    _state(my::AIState::Patrol),
    _enemy_state(my::EnemyState::Move),
    _patrol_behaviour_executor(),
    _combat_behaviour_executor() {
<<<<<<< HEAD
>>>>>>> origin/Ex55_WeaponAction
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
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
    return  this->_attack->GetSphere();
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
   
    //_init_position = super::GetPosition();
    _init_position = Mof::CVector3(5.0f, 0.0f, 5.0f);
    _sight->SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));
    _attack->SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));

    _combat_behaviour_executor =  _behaviour_executor_factory.Create("../Resource/behaviour/combat.json");
    _patrol_behaviour_executor = _behaviour_executor_factory.Create("../Resource/behaviour/patrol.json");

    if (auto mesh = _mesh.lock()) {
        _motion = mesh->CreateMotionController();
        _motion->ChangeMotion(0);
    } // if
<<<<<<< HEAD
<<<<<<< HEAD
    /*
    auto ntnode = std::make_shared<my::NearTargetNode>();
    _rootnode->AddChild(ntnode);
    _behaviour_executor = _rootnode->CreateExecutor();
    */
=======
>>>>>>> origin/Ex55_WeaponAction
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    return true;
}

bool my::Enemy::Input(void) {
<<<<<<< HEAD
<<<<<<< HEAD
    float tilt = 1.0f;
    Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);
    /*
=======
    // ��ɂ�EnemyState�̃����o�Ɏ�������
    auto temp = std::dynamic_pointer_cast<my::Enemy>(shared_from_this());

>>>>>>> origin/Ex55_WeaponAction
    if (_state == my::AIState::Patrol) {
        _patrol_behaviour_executor->Execute(temp);
    } // if
<<<<<<< HEAD
    */
    if (_state != my::AIState::Combat) {

        if (auto target = _target.lock()) {
            auto dir = target->GetPosition() - super::GetPosition();
            float angle = std::atan2(dir.z, dir.x);
            in = math::Rotate(in.x, in.y, angle);

            float angular_speed = 1.0f;
            float speed = 0.1f;
            this->InputMoveAngularVelocity(in, angular_speed);
            this->InputMoveVelocity(in, speed);
        } // if
=======
    else if (_state == my::AIState::Combat) {
        _combat_behaviour_executor->Execute((temp));
>>>>>>> origin/Ex55_WeaponAction
=======
    // 後ににEnemyStateのメンバに持たせる
    auto temp = std::dynamic_pointer_cast<my::Enemy>(shared_from_this());

    if (_state == my::AIState::Patrol) {
        _patrol_behaviour_executor->Execute(temp);
    } // if
    else if (_state == my::AIState::Combat) {
        _combat_behaviour_executor->Execute((temp));
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
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
    return _sight->ContainInRecognitionRange(pos);
}

void my::Enemy::RenderDebug(void) {
    super::RenderDebug();

    // 視線描画
    Mof::Vector3 start = super::GetPosition();
    float h = super::_height;
    start.y += h;

    // 視界境界表示
    this->RenderRay(start, 0.0f);
    this->RenderRay(start, 90.0f);
    this->RenderRay(start, -90.0f);

    // 対象への視線を表示
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
    _attack->RenderDebug();
}