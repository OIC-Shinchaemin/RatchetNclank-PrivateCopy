#include "Enemy.h"

#include "../Behaviour/Node/Node.h"
#include "../Behaviour/Node/SequencerNode.h"
#include "../Behaviour/Node/SelectorNode.h"
#include "../Behaviour/Node/ActionNode.h"
#include "../Behaviour/Node/ConditionalNode.h"
#include "../Behaviour/Node/DecoratorNode.h"


//using BehaviourActor = my::Actor;
// äOïîÇ©ÇÁéÛÇØéÊÇÈ
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
    return Mof::CVector3Utilities::Distance(_init_position, super::GetPosition());
}

bool my::Enemy::HasTarget(void) const {
    return !_target.expired();
}

bool my::Enemy::OverLooking(void) {
    float tilt = 1.0f;
    Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);

    auto angle_y = math::ToDegree(super::GetRotate().y);

    in = math::Rotate(in.x, in.y, ut::GenerateRandomF(0.0f, math::kTwoPi));
    float angular_speed = 4.0f;
    this->InputMoveAngularVelocity(in, angular_speed);
    if (auto target = _target.lock()) {
        _state = my::AIState::Combat;
        _combat_behaviour_executor->Reset();
        return true;
    } // if
    return false;
}

void my::Enemy::ChaseTo(Mof::CVector3 target, float speed, float angular_speed) {
    float tilt = 1.0f;
    Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);

    auto dir = target - super::GetPosition();
    float angle = std::atan2(dir.z, dir.x);
    in = math::Rotate(in.x, in.y, angle);

    this->InputMoveAngularVelocity(in, angular_speed);
    this->InputMoveVelocity(in, speed);
}

bool my::Enemy::Chase(void) {
    if (_target.expired()) {
        _state = my::AIState::Patrol;
        _patrol_behaviour_executor->Reset();
    } // if

    if (auto target = _target.lock()) {
        if (!Mof::CSphere(super::GetPosition(), _sight.GetRange()).CollisionPoint(target->GetPosition())) {
            _target.reset();
            return true;
        } // if
        this->ChaseTo(target->GetPosition(), 0.1f, 1.0f);
    } // if
    return false;
}

bool my::Enemy::GoHome(void) {
    this->ChaseTo(_init_position, 0.1f, 1.0f);
    if (this->GetDistanceFromInitPosition() < 2.0f) {
        return true;
    } // if
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

    this->RenderRay(ray, _sight.GetRange(), def::color_rgba_u32::kGreen);
}

my::Enemy::Enemy() :
    super(),
    _init_position(),
    _target(),
    _sight(),
    _state(my::AIState::Patrol),
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

bool my::Enemy::Initialize(const def::Transform& transform) {
    super::Initialize(transform);
//    _init_position = super::GetPosition();
    _init_position = Mof::CVector3(6.0f, 0.0f, 6.0f);
    _sight.SetOwner(std::dynamic_pointer_cast<my::Enemy>(shared_from_this()));

    _patrol_behaviour_executor = this->CreatePatrolBehaviour();
    _combat_behaviour_executor = this->CreateCombatBehaviour();

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
}