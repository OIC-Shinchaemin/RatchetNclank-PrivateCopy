#include "Enemy.h"

#include "Player.h"
#include "../../Component/Collision/Object/EnemyCollisionObject.h"
#include "../../Component/Collision/Object/EnemySightCollisionObject.h"
#include "../../Component/Enemy/EnemyIdleComponent.h"
#include "../../Component/Enemy/EnemyMoveComponent.h"
#include "../../Component/Enemy/EnemyAttackComponent.h"
#include "../../Component/SightRecognitionComponent.h"
#include "../../Component/AIStateComponent.h"
#include "../../Component/Enemy/EnemyStateComponent.h"


void my::Enemy::RenderRay(const Mof::CRay3D& ray, float length, int color) {
    ::CGraphicsUtilities::RenderLine(ray.Position,
                                     ray.Position + ray.Direction * length,
                                     color);
}

void my::Enemy::RenderRay(Mof::Vector3 start, float degree_y) {
    auto sight = super::GetComponent<my::SightRecognitionComponent>();

    auto ray = Mof::CRay3D(start);
    auto rotate = super::GetRotate();
    rotate.y += math::ToRadian(degree_y);

    Mof::CMatrix44 mat;
    mat.RotationZXY(rotate);
    ray.Direction = -math::vec3::kUnitZ * mat;

    this->RenderRay(ray, sight->GetRange(), def::color_rgba_u32::kGreen);
}

my::Enemy::Enemy() :
    super(),
    _target(){
    super::SetTag("Enemy");
}

my::Enemy::~Enemy() {
}

void my::Enemy::SetTarget(const std::shared_ptr<my::Character>& ptr) {
    this->_target = ptr;
}

std::weak_ptr<my::Actor> my::Enemy::GetTarget(void) const {
    return this->_target;
}

void my::Enemy::GenerateCollisionObject(void) {
    auto coll = super::GetComponent<my::EnemyCollisionObject>();
    coll->AddCollisionFunc(my::CollisionObject::CollisionFuncType::Enter,
                           "PlayerCollisionObject",
                           my::CollisionObject::CollisionFunc([&](const my::CollisionInfo& in) {
        this->End(); return true;
    }));

    auto sight = super::GetComponent<my::SightRecognitionComponent>();
    auto sight_coll = super::GetComponent<my::EnemySightCollisionObject>();
    sight_coll->SetSight(sight);
    sight_coll->AddCollisionFunc(my::CollisionObject::CollisionFuncType::Enter,
                                 "PlayerCollisionObject",
                                 my::CollisionObject::CollisionFunc([&](const my::CollisionInfo& in) {
        auto target = std::any_cast<std::shared_ptr<my::Actor>>(in.target);
        this->SetTarget(std::dynamic_pointer_cast<Player> (target));
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
    // generate
    this->GenerateCollisionObject();

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
}