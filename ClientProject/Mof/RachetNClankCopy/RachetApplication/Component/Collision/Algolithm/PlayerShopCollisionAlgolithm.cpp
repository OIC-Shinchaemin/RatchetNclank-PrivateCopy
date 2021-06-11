#include "PlayerShopCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


ratchet::PlayerShopCollisionAlgolithm::PlayerShopCollisionAlgolithm() :
    super() {
}

ratchet::PlayerShopCollisionAlgolithm::~PlayerShopCollisionAlgolithm() {
}

const char* ratchet::PlayerShopCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* ratchet::PlayerShopCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::CollisionComponentType::kShopCollisionComponent.c_str();
}

bool ratchet::PlayerShopCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::CollisionComponent> object, std::shared_ptr<ratchet::CollisionComponent> target, ratchet::CollisionInfo& out) {
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