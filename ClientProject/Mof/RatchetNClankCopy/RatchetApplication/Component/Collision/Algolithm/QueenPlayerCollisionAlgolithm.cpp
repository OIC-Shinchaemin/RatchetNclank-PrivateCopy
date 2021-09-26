#include "QueenPlayerCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::QueenPlayerCollisionAlgolithm::QueenPlayerCollisionAlgolithm() :
    super() {
}

ratchet::QueenPlayerCollisionAlgolithm::~QueenPlayerCollisionAlgolithm() {
}

const char* ratchet::QueenPlayerCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kQueenCollisionComponent.c_str();
}

const char* ratchet::QueenPlayerCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool ratchet::QueenPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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