#include "EnemyBombGloveBulletCollisionAlgolithm.h"


my::EnemyBombGloveBulletCollisionAlgolithm::EnemyBombGloveBulletCollisionAlgolithm() :
    super() {
}

my::EnemyBombGloveBulletCollisionAlgolithm::~EnemyBombGloveBulletCollisionAlgolithm() {
}

const char* my::EnemyBombGloveBulletCollisionAlgolithm::GetLayerType(void) const {
    return "EnemyCollisionComponent";
}

const char* my::EnemyBombGloveBulletCollisionAlgolithm::GetTargetType(void) const {
    return "BombGloveBulletCollisionComponent";
}

bool my::EnemyBombGloveBulletCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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