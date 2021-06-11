#include "PlayerEnemyMeleeAttackCollisionAlgolithm.h"

#include "Base/Core/Math.h"
#include "../Object/CollisionComponentDefine.h"


rachet::PlayerEnemyMeleeAttackCollisionAlgolithm::PlayerEnemyMeleeAttackCollisionAlgolithm() :
    super() {
}

rachet::PlayerEnemyMeleeAttackCollisionAlgolithm::~PlayerEnemyMeleeAttackCollisionAlgolithm() {
}

const char* rachet::PlayerEnemyMeleeAttackCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* rachet::PlayerEnemyMeleeAttackCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kEnemyMeleeAttackCollisionComponent.c_str();
}

bool rachet::PlayerEnemyMeleeAttackCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        out.target = target->GetOwner();
        out.angle.y = target->GetOwner()->GetRotate().y;
        out.speed = 10.0f;
        return true;
    } // if
    return false;
}