#include "ShipPlayerCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


rachet::ShipPlayerCollisionAlgolithm::ShipPlayerCollisionAlgolithm() :
    super() {
}

rachet::ShipPlayerCollisionAlgolithm::~ShipPlayerCollisionAlgolithm() {
}

const char* rachet::ShipPlayerCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kShipCollisionComponent.c_str();
}

const char* rachet::ShipPlayerCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool rachet::ShipPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
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