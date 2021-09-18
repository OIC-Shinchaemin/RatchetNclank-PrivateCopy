#include "BlasterBulletScarecrowCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::BlasterBulletScarecrowCollisionAlgolithm::BlasterBulletScarecrowCollisionAlgolithm() :
    super() {
}

ratchet::BlasterBulletScarecrowCollisionAlgolithm::~BlasterBulletScarecrowCollisionAlgolithm() {
}

const char* ratchet::BlasterBulletScarecrowCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBlasterBulletCollisionComponent.c_str();
}

const char* ratchet::BlasterBulletScarecrowCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kScarecrowCollisionComponent.c_str();
}

bool ratchet::BlasterBulletScarecrowCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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