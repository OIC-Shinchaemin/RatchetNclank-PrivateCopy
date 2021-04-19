#include "BombGloveBulletComponent.h"

#include "../Collision/Object/BombGloveBulletCollisionComponent.h"


my::BombGloveBulletComponent::BombGloveBulletComponent(int priority) :
    super(priority) {
}

my::BombGloveBulletComponent::BombGloveBulletComponent(const BombGloveBulletComponent& obj) :
    super(obj) {
}

my::BombGloveBulletComponent::~BombGloveBulletComponent() {
}

std::string my::BombGloveBulletComponent::GetType(void) const {
    return "BombGloveBulletComponent";
}

bool my::BombGloveBulletComponent::Initialize(void) {
    super::Initialize();
    super::Start();

    auto coll_com = super::GetOwner()->GetComponent<my::BombGloveBulletCollisionComponent>();
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               "EnemyCollisionComponent",
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        // expord start
        super::GetOwner()->End();
        return true;
    }));
    return true;
}

bool my::BombGloveBulletComponent::Update(float delta_time) {
    return true;
}

bool my::BombGloveBulletComponent::Render(void) {
    return true;
}

bool my::BombGloveBulletComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::BombGloveBulletComponent::Clone(void) {
    return std::make_shared<my::BombGloveBulletComponent>(*this);
}