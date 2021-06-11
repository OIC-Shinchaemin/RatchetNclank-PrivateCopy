#include "BlasterBulletEnemyCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


rachet::BlasterBulletEnemyCollisionAlgolithm::BlasterBulletEnemyCollisionAlgolithm() :
    super() {
}

rachet::BlasterBulletEnemyCollisionAlgolithm::~BlasterBulletEnemyCollisionAlgolithm() {
}

const char* rachet::BlasterBulletEnemyCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kBlasterBulletCollisionComponent.c_str();
}

const char* rachet::BlasterBulletEnemyCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

bool rachet::BlasterBulletEnemyCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
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