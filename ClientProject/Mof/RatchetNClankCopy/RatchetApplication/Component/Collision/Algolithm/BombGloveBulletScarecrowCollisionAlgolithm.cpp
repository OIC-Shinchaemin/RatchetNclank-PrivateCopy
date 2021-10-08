#include "BombGloveBulletScarecrowCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::BombGloveBulletScarecrowCollisionAlgolithm::BombGloveBulletScarecrowCollisionAlgolithm() :
    super() {
}

ratchet::BombGloveBulletScarecrowCollisionAlgolithm::~BombGloveBulletScarecrowCollisionAlgolithm() {
}

const char* ratchet::BombGloveBulletScarecrowCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBombGloveBulletCollisionComponent.c_str();
}

const char* ratchet::BombGloveBulletScarecrowCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kScarecrowCollisionComponent.c_str();
}

bool ratchet::BombGloveBulletScarecrowCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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