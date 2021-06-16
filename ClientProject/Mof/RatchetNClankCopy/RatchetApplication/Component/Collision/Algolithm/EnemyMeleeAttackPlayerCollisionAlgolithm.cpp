#include "EnemyMeleeAttackPlayerCollisionAlgolithm.h"

#include "Base/Core/Math.h"
#include "../Object/CollisionComponentDefine.h"


ratchet::EnemyMeleeAttackPlayerCollisionAlgolithm::EnemyMeleeAttackPlayerCollisionAlgolithm() :
    super() {
}

ratchet::EnemyMeleeAttackPlayerCollisionAlgolithm::~EnemyMeleeAttackPlayerCollisionAlgolithm() {
}

const char* ratchet::EnemyMeleeAttackPlayerCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kEnemyMeleeAttackCollisionComponent.c_str();
}

const char* ratchet::EnemyMeleeAttackPlayerCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool ratchet::EnemyMeleeAttackPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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