#include "EnemyPlayerCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


rachet::EnemyPlayerCollisionAlgolithm::EnemyPlayerCollisionAlgolithm() :
    super() {
}

rachet::EnemyPlayerCollisionAlgolithm::~EnemyPlayerCollisionAlgolithm() {
}

const char* rachet::EnemyPlayerCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

const char* rachet::EnemyPlayerCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool rachet::EnemyPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
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