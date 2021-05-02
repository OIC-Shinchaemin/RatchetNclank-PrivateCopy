#include "EnemyAttackPlayerCollisionAlgolithm.h"

#include "My/Core/Math.h"
#include "../Object/CollisionComponentDefine.h"


my::EnemyAttackPlayerCollisionAlgolithm::EnemyAttackPlayerCollisionAlgolithm() :
    super() {
}

my::EnemyAttackPlayerCollisionAlgolithm::~EnemyAttackPlayerCollisionAlgolithm() {
}

const char* my::EnemyAttackPlayerCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kEnemyAttackCollisionComponent.c_str();
    //return "EnemyAttackCollisionComponent";
}

const char* my::EnemyAttackPlayerCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kPlayerCollisionComponent.c_str();
    //return "PlayerCollisionComponent";
}

bool my::EnemyAttackPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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