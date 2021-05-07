#include "EnemyEnemyCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


my::EnemyEnemyCollisionAlgolithm::EnemyEnemyCollisionAlgolithm() :
    super() {
}

my::EnemyEnemyCollisionAlgolithm::~EnemyEnemyCollisionAlgolithm() {
}

const char* my::EnemyEnemyCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

const char* my::EnemyEnemyCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

bool my::EnemyEnemyCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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