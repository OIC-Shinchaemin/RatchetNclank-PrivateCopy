#include "BoltPlayerCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


ratchet::BoltPlayerCollisionAlgolithm::BoltPlayerCollisionAlgolithm() :
    super() {
}

ratchet::BoltPlayerCollisionAlgolithm::~BoltPlayerCollisionAlgolithm() {
}

const char* ratchet::BoltPlayerCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBoltCollisionComponent.c_str();
}

const char* ratchet::BoltPlayerCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool ratchet::BoltPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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