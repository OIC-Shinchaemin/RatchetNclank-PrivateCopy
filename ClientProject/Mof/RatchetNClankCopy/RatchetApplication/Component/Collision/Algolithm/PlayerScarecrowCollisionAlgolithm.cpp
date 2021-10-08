#include "PlayerScarecrowCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::PlayerScarecrowCollisionAlgolithm::PlayerScarecrowCollisionAlgolithm() :
    super() {
}

ratchet::PlayerScarecrowCollisionAlgolithm::~PlayerScarecrowCollisionAlgolithm() {
}

const char* ratchet::PlayerScarecrowCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* ratchet::PlayerScarecrowCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kScarecrowCollisionComponent.c_str();
}

bool ratchet::PlayerScarecrowCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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