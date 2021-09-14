#include "EnemyEnemyCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::EnemyEnemyCollisionAlgolithm::EnemyEnemyCollisionAlgolithm() :
    super() {
}

ratchet::EnemyEnemyCollisionAlgolithm::~EnemyEnemyCollisionAlgolithm() {
}

const char* ratchet::EnemyEnemyCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

const char* ratchet::EnemyEnemyCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

bool ratchet::EnemyEnemyCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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