#include "EnemyBlasterBulletCollisionAlgolithm.h"


my::EnemyBlasterBulletCollisionAlgolithm::EnemyBlasterBulletCollisionAlgolithm() :
    super() {
}

my::EnemyBlasterBulletCollisionAlgolithm::~EnemyBlasterBulletCollisionAlgolithm() {
}

const char* my::EnemyBlasterBulletCollisionAlgolithm::GetLayerType(void) const {
    return "EnemyCollisionComponent";
}

const char* my::EnemyBlasterBulletCollisionAlgolithm::GetTargetType(void) const {
    return "BlasterBulletCollisionComponent";
}

bool my::EnemyBlasterBulletCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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