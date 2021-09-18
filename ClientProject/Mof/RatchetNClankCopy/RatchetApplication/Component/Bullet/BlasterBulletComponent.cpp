#include "BlasterBulletComponent.h"

#include "../Collision/Object/BlasterBulletCollisionComponent.h"


ratchet::component::bullet::BlasterBulletComponent::BlasterBulletComponent(int priority) :
    super(priority) {
}

ratchet::component::bullet::BlasterBulletComponent::BlasterBulletComponent(const BlasterBulletComponent& obj) :
    super(obj) {
}

ratchet::component::bullet::BlasterBulletComponent::~BlasterBulletComponent() {
}

std::string ratchet::component::bullet::BlasterBulletComponent::GetType(void) const {
    return "BlasterBulletComponent";
}

bool ratchet::component::bullet::BlasterBulletComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    auto coll_com = super::GetOwner()->GetComponent<ratchet::component::collision::BlasterBulletCollisionComponent>();

    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               "EnemyCollisionComponent",
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));
    coll_com->AddCollisionFunc(ratchet::component::collision::CollisionComponent::CollisionFuncType::Enter,
                               "ScarecrowCollisionComponent",
                               ratchet::component::collision::CollisionComponent::CollisionFunc([&](const component::collision::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));

    return true;
}

bool ratchet::component::bullet::BlasterBulletComponent::Update(float delta_time) {
    return true;
}

bool ratchet::component::bullet::BlasterBulletComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::bullet::BlasterBulletComponent::Clone(void) {
    return std::make_shared<ratchet::component::bullet::BlasterBulletComponent>(*this);
}