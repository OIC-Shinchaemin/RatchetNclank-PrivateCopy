#include "BulletItemPlayerCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


rachet::BulletItemPlayerCollisionAlgolithm::BulletItemPlayerCollisionAlgolithm() :
    super() {
}

rachet::BulletItemPlayerCollisionAlgolithm::~BulletItemPlayerCollisionAlgolithm() {
}

const char* rachet::BulletItemPlayerCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kBulletItemCollisionComponent.c_str();
}

const char* rachet::BulletItemPlayerCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool rachet::BulletItemPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
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