#include "PlayerEnemyAttackCollisionAlgolithm.h"

#include "My/Core/Math.h"
#include "../Object/CollisionComponentDefine.h"


my::PlayerEnemyAttackCollisionAlgolithm::PlayerEnemyAttackCollisionAlgolithm() :
    super() {
}

my::PlayerEnemyAttackCollisionAlgolithm::~PlayerEnemyAttackCollisionAlgolithm() {
}

const char* my::PlayerEnemyAttackCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* my::PlayerEnemyAttackCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kEnemyAttackCollisionComponent.c_str();
}

bool my::PlayerEnemyAttackCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        out.target = target->GetOwner();
        auto pos = object->GetOwner()->GetPosition();
        auto target_pos = target->GetOwner()->GetPosition();
        out.angle.y = target->GetOwner()->GetRotate().y;
        return true;
    } // if
    return false;
}