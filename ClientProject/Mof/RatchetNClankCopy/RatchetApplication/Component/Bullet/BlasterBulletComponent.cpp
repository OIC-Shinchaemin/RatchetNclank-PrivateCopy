#include "BlasterBulletComponent.h"

#include "../Collision/Object/BlasterBulletCollisionComponent.h"


ratchet::BlasterBulletComponent::BlasterBulletComponent(int priority) :
    super(priority) {
}

ratchet::BlasterBulletComponent::BlasterBulletComponent(const BlasterBulletComponent& obj) :
    super(obj) {
}

ratchet::BlasterBulletComponent::~BlasterBulletComponent() {
}

std::string ratchet::BlasterBulletComponent::GetType(void) const {
    return "BlasterBulletComponent";
}

bool ratchet::BlasterBulletComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    auto coll_com = super::GetOwner()->GetComponent<ratchet::BlasterBulletCollisionComponent>();
    coll_com->AddCollisionFunc(ratchet::CollisionComponent::CollisionFuncType::Enter,
                               "EnemyCollisionComponent",
                               ratchet::CollisionComponent::CollisionFunc([&](const ratchet::CollisionInfo& in) {
        super::GetOwner()->End();
        return true;
    }));
    return true;
}

bool ratchet::BlasterBulletComponent::Update(float delta_time) {
    return true;
}

bool ratchet::BlasterBulletComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::BlasterBulletComponent::Clone(void) {
    return std::make_shared<ratchet::BlasterBulletComponent>(*this);
}