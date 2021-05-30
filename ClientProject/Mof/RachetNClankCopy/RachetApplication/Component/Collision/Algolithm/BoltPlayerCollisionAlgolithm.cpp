#include "BoltPlayerCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


my::BoltPlayerCollisionAlgolithm::BoltPlayerCollisionAlgolithm() :
    super() {
}

my::BoltPlayerCollisionAlgolithm::~BoltPlayerCollisionAlgolithm() {
}

const char* my::BoltPlayerCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kBoltCollisionComponent.c_str();
}

const char* my::BoltPlayerCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool my::BoltPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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