#include "BlasterBulletComponent.h"

#include "../Collision/Object/BlasterBulletCollisionComponent.h"


rachet::BlasterBulletComponent::BlasterBulletComponent(int priority) :
    super(priority) {
}

rachet::BlasterBulletComponent::BlasterBulletComponent(const BlasterBulletComponent& obj) :
    super(obj) {
}

rachet::BlasterBulletComponent::~BlasterBulletComponent() {
}

std::string rachet::BlasterBulletComponent::GetType(void) const {
    return "BlasterBulletComponent";
}

bool rachet::BlasterBulletComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    auto coll_com = super::GetOwner()->GetComponent<rachet::BlasterBulletCollisionComponent>();
    coll_com->AddCollisionFunc(rachet::CollisionComponent::CollisionFuncType::Enter,
                               "EnemyCollisionComponent",
                               rachet::CollisionComponent::CollisionFunc([&](const rachet::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));
    return true;
}

bool rachet::BlasterBulletComponent::Update(float delta_time) {
    return true;
}

bool rachet::BlasterBulletComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::BlasterBulletComponent::Clone(void) {
    return std::make_shared<rachet::BlasterBulletComponent>(*this);
}