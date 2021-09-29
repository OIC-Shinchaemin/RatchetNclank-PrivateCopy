#include "PlayerFenceCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::PlayerFenceCollisionAlgolithm::PlayerFenceCollisionAlgolithm() :
    super() {
}

ratchet::PlayerFenceCollisionAlgolithm::~PlayerFenceCollisionAlgolithm() {
}

const char* ratchet::PlayerFenceCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* ratchet::PlayerFenceCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kFenceCollisionComponent.c_str();
}

bool ratchet::PlayerFenceCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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