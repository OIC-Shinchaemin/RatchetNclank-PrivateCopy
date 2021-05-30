#include "PlayerEnemyMeleeAttackCollisionAlgolithm.h"

#include "My/Core/Math.h"
#include "../Object/CollisionComponentDefine.h"


my::PlayerEnemyMeleeAttackCollisionAlgolithm::PlayerEnemyMeleeAttackCollisionAlgolithm() :
    super() {
}

my::PlayerEnemyMeleeAttackCollisionAlgolithm::~PlayerEnemyMeleeAttackCollisionAlgolithm() {
}

const char* my::PlayerEnemyMeleeAttackCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* my::PlayerEnemyMeleeAttackCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kEnemyMeleeAttackCollisionComponent.c_str();
}

bool my::PlayerEnemyMeleeAttackCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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