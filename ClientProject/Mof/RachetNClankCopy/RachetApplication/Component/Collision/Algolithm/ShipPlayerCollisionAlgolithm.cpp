#include "ShipPlayerCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


ratchet::ShipPlayerCollisionAlgolithm::ShipPlayerCollisionAlgolithm() :
    super() {
}

ratchet::ShipPlayerCollisionAlgolithm::~ShipPlayerCollisionAlgolithm() {
}

const char* ratchet::ShipPlayerCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::CollisionComponentType::kShipCollisionComponent.c_str();
}

const char* ratchet::ShipPlayerCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool ratchet::ShipPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::CollisionComponent> object, std::shared_ptr<ratchet::CollisionComponent> target, ratchet::CollisionInfo& out) {
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