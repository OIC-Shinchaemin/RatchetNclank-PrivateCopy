#include "BoltPlayerCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


rachet::BoltPlayerCollisionAlgolithm::BoltPlayerCollisionAlgolithm() :
    super() {
}

rachet::BoltPlayerCollisionAlgolithm::~BoltPlayerCollisionAlgolithm() {
}

const char* rachet::BoltPlayerCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kBoltCollisionComponent.c_str();
}

const char* rachet::BoltPlayerCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool rachet::BoltPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
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