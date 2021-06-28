#include "PlayerEnemyMeleeAttackCollisionAlgolithm.h"

#include "Base/Core/Math.h"
#include "../Object/CollisionComponentDefine.h"


ratchet::PlayerEnemyMeleeAttackCollisionAlgolithm::PlayerEnemyMeleeAttackCollisionAlgolithm() :
    super() {
}

ratchet::PlayerEnemyMeleeAttackCollisionAlgolithm::~PlayerEnemyMeleeAttackCollisionAlgolithm() {
}

const char* ratchet::PlayerEnemyMeleeAttackCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* ratchet::PlayerEnemyMeleeAttackCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kEnemyMeleeAttackCollisionComponent.c_str();
}

bool ratchet::PlayerEnemyMeleeAttackCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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