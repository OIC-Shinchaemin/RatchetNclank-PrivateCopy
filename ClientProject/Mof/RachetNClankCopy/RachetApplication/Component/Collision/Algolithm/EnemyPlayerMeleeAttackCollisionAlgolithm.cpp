#include "EnemyPlayerMeleeAttackCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


my::EnemyPlayerMeleeAttackCollisionAlgolithm::EnemyPlayerMeleeAttackCollisionAlgolithm() :
    super() {
}

my::EnemyPlayerMeleeAttackCollisionAlgolithm::~EnemyPlayerMeleeAttackCollisionAlgolithm() {
}

const char* my::EnemyPlayerMeleeAttackCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

const char* my::EnemyPlayerMeleeAttackCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kPlayerMeleeAttackCollisionComponent.c_str();
}

bool my::EnemyPlayerMeleeAttackCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
    // 衝突オブジェクトを持っていないなら処理しない
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        out.target = target->GetOwner();
        
        Mof::CVector3 direction = object->GetOwner()->GetPosition() - target->GetOwner()->GetPosition();
        out.angle.y = std::atan2(-direction.z, direction.x) + math::kHalfPi;

        return true;
    } // if
    return false;
}