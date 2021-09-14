#include "EnemyPlayerMeleeAttackCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::EnemyPlayerMeleeAttackCollisionAlgolithm::EnemyPlayerMeleeAttackCollisionAlgolithm() :
    super() {
}

ratchet::EnemyPlayerMeleeAttackCollisionAlgolithm::~EnemyPlayerMeleeAttackCollisionAlgolithm() {
}

const char* ratchet::EnemyPlayerMeleeAttackCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

const char* ratchet::EnemyPlayerMeleeAttackCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerMeleeAttackCollisionComponent.c_str();
}

bool ratchet::EnemyPlayerMeleeAttackCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
    // 衝突オブジェクトを持っていないなら処理しない
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        out.target = target->GetOwner();
        
        Mof::CVector3 direction = object->GetOwner()->GetPosition() - target->GetOwner()->GetPosition();
        out.angle.y = std::atan2(-direction.z, direction.x) + math::kHalfPi;
        out.speed = 30.0f;
        return true;
    } // if
    return false;
}