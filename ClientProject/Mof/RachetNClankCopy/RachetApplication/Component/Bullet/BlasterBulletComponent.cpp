#include "BlasterBulletComponent.h"

#include "../Collision/Object/BlasterBulletCollisionComponent.h"


my::BlasterBulletComponent::BlasterBulletComponent(int priority) :
    super(priority) {
}

my::BlasterBulletComponent::BlasterBulletComponent(const BlasterBulletComponent& obj) :
    super(obj) {
}

my::BlasterBulletComponent::~BlasterBulletComponent() {
}

std::string my::BlasterBulletComponent::GetType(void) const {
    return "BlasterBulletComponent";
}

bool my::BlasterBulletComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    auto coll_com = super::GetOwner()->GetComponent<my::BlasterBulletCollisionComponent>();
    coll_com->AddCollisionFunc(my::CollisionComponent::CollisionFuncType::Enter,
                               "EnemyCollisionComponent",
                               my::CollisionComponent::CollisionFunc([&](const my::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));
    return true;
}

bool my::BlasterBulletComponent::Update(float delta_time) {
    return true;
}

bool my::BlasterBulletComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::BlasterBulletComponent::Clone(void) {
    return std::make_shared<my::BlasterBulletComponent>(*this);
}