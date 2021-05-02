#include "PlayerShipCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


my::PlayerShipCollisionAlgolithm::PlayerShipCollisionAlgolithm() :
    super() {
}

my::PlayerShipCollisionAlgolithm::~PlayerShipCollisionAlgolithm() {
}

const char* my::PlayerShipCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* my::PlayerShipCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kShipCollisionComponent.c_str();
}

bool my::PlayerShipCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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