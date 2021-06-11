#include "BombGloveBulletEnemyCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


ratchet::BombGloveBulletEnemyCollisionAlgolithm::BombGloveBulletEnemyCollisionAlgolithm() :
    super() {
}

ratchet::BombGloveBulletEnemyCollisionAlgolithm::~BombGloveBulletEnemyCollisionAlgolithm() {
}

const char* ratchet::BombGloveBulletEnemyCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::CollisionComponentType::kBombGloveBulletCollisionComponent.c_str();
}

const char* ratchet::BombGloveBulletEnemyCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

bool ratchet::BombGloveBulletEnemyCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::CollisionComponent> object, std::shared_ptr<ratchet::CollisionComponent> target, ratchet::CollisionInfo& out) {
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