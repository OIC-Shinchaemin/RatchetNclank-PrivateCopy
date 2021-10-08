#include "BlasterBulletEnemyCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::BlasterBulletEnemyCollisionAlgolithm::BlasterBulletEnemyCollisionAlgolithm() :
    super() {
}

ratchet::BlasterBulletEnemyCollisionAlgolithm::~BlasterBulletEnemyCollisionAlgolithm() {
}

const char* ratchet::BlasterBulletEnemyCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBlasterBulletCollisionComponent.c_str();
}

const char* ratchet::BlasterBulletEnemyCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

bool ratchet::BlasterBulletEnemyCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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