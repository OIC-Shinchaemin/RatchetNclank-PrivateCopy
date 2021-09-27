#include "PlayerBarricadeCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::PlayerBarricadeCollisionAlgolithm::PlayerBarricadeCollisionAlgolithm() :
    super() {
}

ratchet::PlayerBarricadeCollisionAlgolithm::~PlayerBarricadeCollisionAlgolithm() {
}

const char* ratchet::PlayerBarricadeCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* ratchet::PlayerBarricadeCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBarricadeCollisionComponent.c_str();
}

bool ratchet::PlayerBarricadeCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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