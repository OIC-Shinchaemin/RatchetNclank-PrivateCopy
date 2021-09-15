#include "PlayerShipCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::PlayerShipCollisionAlgolithm::PlayerShipCollisionAlgolithm() :
    super() {
}

ratchet::PlayerShipCollisionAlgolithm::~PlayerShipCollisionAlgolithm() {
}

const char* ratchet::PlayerShipCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* ratchet::PlayerShipCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kShipCollisionComponent.c_str();
}

bool ratchet::PlayerShipCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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