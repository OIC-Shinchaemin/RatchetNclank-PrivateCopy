#include "PlayerEnemyAttackCollisionAlgolithm.h"

#include "My/Core/Math.h"


my::PlayerEnemyAttackCollisionAlgolithm::PlayerEnemyAttackCollisionAlgolithm() :
    super() {
}

my::PlayerEnemyAttackCollisionAlgolithm::~PlayerEnemyAttackCollisionAlgolithm() {
}

const char* my::PlayerEnemyAttackCollisionAlgolithm::GetLayerType(void) const {
    return "PlayerCollisionObject";
}

const char* my::PlayerEnemyAttackCollisionAlgolithm::GetTargetType(void) const {
    return "EnemyAttackCollisionObject";
}

bool my::PlayerEnemyAttackCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionObject> object, std::shared_ptr<my::CollisionObject> target, my::CollisionInfo& out) {
    // 衝突オブジェクトを持っていないなら処理しない
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        out.target = target->GetOwner();
        return true;
    } // if

    auto player = object->GetSphere().value();
    auto enemy = target->GetSphere().value();
    return false;
}