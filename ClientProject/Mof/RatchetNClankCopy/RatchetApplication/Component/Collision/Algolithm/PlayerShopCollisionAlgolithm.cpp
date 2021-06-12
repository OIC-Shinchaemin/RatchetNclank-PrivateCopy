#include "PlayerShopCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


ratchet::PlayerShopCollisionAlgolithm::PlayerShopCollisionAlgolithm() :
    super() {
}

ratchet::PlayerShopCollisionAlgolithm::~PlayerShopCollisionAlgolithm() {
}

const char* ratchet::PlayerShopCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* ratchet::PlayerShopCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kShopCollisionComponent.c_str();
}

bool ratchet::PlayerShopCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
    // 衝突オブジェクトを持っていないなら処理しない
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        out.target = target->GetOwner();
        return true;
    } // if
    return false;
}