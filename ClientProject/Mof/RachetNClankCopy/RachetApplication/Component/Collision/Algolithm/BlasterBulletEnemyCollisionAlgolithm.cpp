#include "BlasterBulletEnemyCollisionAlgolithm.h"


my::BlasterBulletEnemyCollisionAlgolithm::BlasterBulletEnemyCollisionAlgolithm() :
    super() {
}

my::BlasterBulletEnemyCollisionAlgolithm::~BlasterBulletEnemyCollisionAlgolithm() {
}

const char* my::BlasterBulletEnemyCollisionAlgolithm::GetLayerType(void) const {
    return "BlasterBulletCollisionComponent";
}

const char* my::BlasterBulletEnemyCollisionAlgolithm::GetTargetType(void) const {
    return "EnemyCollisionComponent";
}

bool my::BlasterBulletEnemyCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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