#include "EnemyBombGloveBulletCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


rachet::EnemyBombGloveBulletCollisionAlgolithm::EnemyBombGloveBulletCollisionAlgolithm() :
    super() {
}

rachet::EnemyBombGloveBulletCollisionAlgolithm::~EnemyBombGloveBulletCollisionAlgolithm() {
}

const char* rachet::EnemyBombGloveBulletCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

const char* rachet::EnemyBombGloveBulletCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kBombGloveBulletCollisionComponent.c_str();
}

bool rachet::EnemyBombGloveBulletCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
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