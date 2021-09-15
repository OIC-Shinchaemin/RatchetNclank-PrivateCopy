#include "EnemyBombGloveBulletCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::EnemyBombGloveBulletCollisionAlgolithm::EnemyBombGloveBulletCollisionAlgolithm() :
    super() {
}

ratchet::EnemyBombGloveBulletCollisionAlgolithm::~EnemyBombGloveBulletCollisionAlgolithm() {
}

const char* ratchet::EnemyBombGloveBulletCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

const char* ratchet::EnemyBombGloveBulletCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBombGloveBulletCollisionComponent.c_str();
}

bool ratchet::EnemyBombGloveBulletCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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