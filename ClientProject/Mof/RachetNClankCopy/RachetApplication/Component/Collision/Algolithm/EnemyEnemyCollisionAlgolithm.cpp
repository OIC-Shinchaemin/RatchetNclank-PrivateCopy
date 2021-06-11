#include "EnemyEnemyCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


rachet::EnemyEnemyCollisionAlgolithm::EnemyEnemyCollisionAlgolithm() :
    super() {
}

rachet::EnemyEnemyCollisionAlgolithm::~EnemyEnemyCollisionAlgolithm() {
}

const char* rachet::EnemyEnemyCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

const char* rachet::EnemyEnemyCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

bool rachet::EnemyEnemyCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
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