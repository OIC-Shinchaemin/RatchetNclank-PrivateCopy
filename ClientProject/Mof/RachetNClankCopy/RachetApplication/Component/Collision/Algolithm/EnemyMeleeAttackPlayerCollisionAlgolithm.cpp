#include "EnemyMeleeAttackPlayerCollisionAlgolithm.h"

#include "Base/Core/Math.h"
#include "../Object/CollisionComponentDefine.h"


rachet::EnemyMeleeAttackPlayerCollisionAlgolithm::EnemyMeleeAttackPlayerCollisionAlgolithm() :
    super() {
}

rachet::EnemyMeleeAttackPlayerCollisionAlgolithm::~EnemyMeleeAttackPlayerCollisionAlgolithm() {
}

const char* rachet::EnemyMeleeAttackPlayerCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kEnemyMeleeAttackCollisionComponent.c_str();
}

const char* rachet::EnemyMeleeAttackPlayerCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool rachet::EnemyMeleeAttackPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
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