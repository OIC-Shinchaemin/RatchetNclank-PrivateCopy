#include "EnemyComponent.h"

#include "../../Gamepad.h"
#include "../Enemy/EnemyDamageComponent.h"
#include "../SightRecognitionComponent.h"
#include "../Collision/Object/EnemyCollisionComponent.h"
#include "../Collision/Object/SightCollisionComponent.h"
#include "../Collision/Object/EnemyAttackCollisionComponent.h"


my::EnemyComponent::EnemyComponent(int priority) :
    super(priority),
    _target() {
    super::_volume = 0.5f;
    super::_height = 1.0f;
}

my::EnemyComponent::EnemyComponent(const EnemyComponent& obj) :
    super(obj),
    _target() {
}

my::EnemyComponent::~EnemyComponent() {
}

void my::EnemyComponent::SetTarget(const std::shared_ptr<my::Actor>& ptr) {
    this->_target = ptr;
}

std::string my::EnemyComponent::GetType(void) const {
    return "EnemyComponent";
}

std::weak_ptr<my::Actor> my::EnemyComponent::GetTarget(void) const {
    return this->_target;
}

bool my::EnemyComponent::Initialize(void) {
    super::Initialize();
    super::Start();
    auto coll_com = super::GetOwner()->GetComponent<my::EnemyCollisionComponent>();
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                           "PlayerCollisionComponent",
                           my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        super::GetOwner()->End(); 
        return true;
    }));
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               "PyrocitorBulletCollisionComponent",
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        super::GetOwner()->GetComponent<my::EnemyDamageComponent>()->Start();
        return true;
    }));

    
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               "BlasterBulletCollisionComponent",
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        super::GetOwner()->GetComponent<my::EnemyDamageComponent>()->Start();
        return true;
    }));

    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               "BombGloveEffectCollisionComponent",
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        super::GetOwner()->GetComponent<my::EnemyDamageComponent>()->Start();
        return true;
    }));


    auto sight_coll = super::GetOwner()->GetComponent<my::SightCollisionComponent>();
    sight_coll->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                                 "PlayerCollisionComponent",
                                 my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        auto target = std::any_cast<std::shared_ptr<my::Actor>>(in.target);
        this->SetTarget(target);
        return true;
    }));
    sight_coll->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Exit,
                                 "PlayerCollisionComponent",
                                 my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        this->SetTarget(nullptr);
        return true;
    }));
    return true;
}

bool my::EnemyComponent::Update(float delta_time) {
    return true;
}

bool my::EnemyComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::EnemyComponent::Clone(void) {
    return std::make_shared<my::EnemyComponent>(*this);
}