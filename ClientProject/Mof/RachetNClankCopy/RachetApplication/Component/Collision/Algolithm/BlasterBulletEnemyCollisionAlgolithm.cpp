#include "BlasterBulletEnemyCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


ratchet::BlasterBulletEnemyCollisionAlgolithm::BlasterBulletEnemyCollisionAlgolithm() :
    super() {
}

ratchet::BlasterBulletEnemyCollisionAlgolithm::~BlasterBulletEnemyCollisionAlgolithm() {
}

const char* ratchet::BlasterBulletEnemyCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::CollisionComponentType::kBlasterBulletCollisionComponent.c_str();
}

const char* ratchet::BlasterBulletEnemyCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

bool ratchet::BlasterBulletEnemyCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::CollisionComponent> object, std::shared_ptr<ratchet::CollisionComponent> target, ratchet::CollisionInfo& out) {
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