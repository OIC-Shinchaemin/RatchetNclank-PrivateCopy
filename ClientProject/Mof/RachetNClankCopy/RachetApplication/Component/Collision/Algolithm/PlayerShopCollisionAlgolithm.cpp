#include "PlayerShopCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


rachet::PlayerShopCollisionAlgolithm::PlayerShopCollisionAlgolithm() :
    super() {
}

rachet::PlayerShopCollisionAlgolithm::~PlayerShopCollisionAlgolithm() {
}

const char* rachet::PlayerShopCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* rachet::PlayerShopCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kShopCollisionComponent.c_str();
}

bool rachet::PlayerShopCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
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