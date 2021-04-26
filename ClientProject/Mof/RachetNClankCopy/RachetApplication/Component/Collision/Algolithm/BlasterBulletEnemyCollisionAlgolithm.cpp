#include "BlasterBulletEnemyCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


my::BlasterBulletEnemyCollisionAlgolithm::BlasterBulletEnemyCollisionAlgolithm() :
    super() {
}

my::BlasterBulletEnemyCollisionAlgolithm::~BlasterBulletEnemyCollisionAlgolithm() {
}

const char* my::BlasterBulletEnemyCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kBlasterBulletCollisionComponent.c_str();
}

const char* my::BlasterBulletEnemyCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kEnemyCollisionComponent.c_str();
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