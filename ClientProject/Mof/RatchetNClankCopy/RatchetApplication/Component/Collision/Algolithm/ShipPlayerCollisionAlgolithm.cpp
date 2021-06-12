#include "ShipPlayerCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


ratchet::ShipPlayerCollisionAlgolithm::ShipPlayerCollisionAlgolithm() :
    super() {
}

ratchet::ShipPlayerCollisionAlgolithm::~ShipPlayerCollisionAlgolithm() {
}

const char* ratchet::ShipPlayerCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kShipCollisionComponent.c_str();
}

const char* ratchet::ShipPlayerCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool ratchet::ShipPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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