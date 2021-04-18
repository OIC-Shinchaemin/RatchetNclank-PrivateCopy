#include "EnemyComponent.h"

#include "../../Gamepad.h"
#include "../Enemy/EnemyDamageComponent.h"
#include "../SightRecognitionComponent.h"
#include "../Collision/Object/EnemyCollisionComponent.h"
#include "../Collision/Object/EnemySightCollisionComponent.h"
#include "../Collision/Object/EnemyAttackCollisionComponent.h"


my::EnemyComponent::EnemyComponent(int priority) :
    super(priority),
    _volume(0.5f),
    _height(1.0f),
    _target() {
}

my::EnemyComponent::EnemyComponent(const EnemyComponent& obj) :
    super(obj),
    _volume(obj._volume),
    _height(obj._height),
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

float my::EnemyComponent::GetVolume(void) const {
    return this->_volume;
}

float my::EnemyComponent::GetHeight(void) const {
    return this->_height;
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
                               "BlasterBulletCollisionComponent",
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        super::GetOwner()->GetComponent<my::EnemyDamageComponent>()->Start();
        return true;
    }));
    auto sight_coll = super::GetOwner()->GetComponent<my::EnemySightCollisionComponent>();
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

bool my::EnemyComponent::Render(void) {
    auto coll_com = super::GetOwner()->GetComponent<my::EnemyCollisionComponent>();
    if (coll_com->GetSphere().has_value()) {
        ::CGraphicsUtilities::RenderLineSphere(coll_com->GetSphere().value(), def::color_rgba::kCyan);
    } // if
    return true;
}

bool my::EnemyComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::EnemyComponent::Clone(void) {
    return std::make_shared<my::EnemyComponent>(*this);
}