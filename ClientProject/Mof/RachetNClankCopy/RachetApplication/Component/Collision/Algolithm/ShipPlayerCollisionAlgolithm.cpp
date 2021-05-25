#include "ShipPlayerCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


my::ShipPlayerCollisionAlgolithm::ShipPlayerCollisionAlgolithm() :
    super() {
}

my::ShipPlayerCollisionAlgolithm::~ShipPlayerCollisionAlgolithm() {
}

const char* my::ShipPlayerCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kShipCollisionComponent.c_str();
}

const char* my::ShipPlayerCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool my::ShipPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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