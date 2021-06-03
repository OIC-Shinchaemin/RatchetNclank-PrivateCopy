#include "PlayerShopCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


my::PlayerShopCollisionAlgolithm::PlayerShopCollisionAlgolithm() :
    super() {
}

my::PlayerShopCollisionAlgolithm::~PlayerShopCollisionAlgolithm() {
}

const char* my::PlayerShopCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* my::PlayerShopCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kShopCollisionComponent.c_str();
}

bool my::PlayerShopCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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