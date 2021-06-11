#include "PlayerEnemyBulletCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


rachet::PlayerEnemyBulletCollisionAlgolithm::PlayerEnemyBulletCollisionAlgolithm() :
    super() {
}

rachet::PlayerEnemyBulletCollisionAlgolithm::~PlayerEnemyBulletCollisionAlgolithm() {
}

const char* rachet::PlayerEnemyBulletCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* rachet::PlayerEnemyBulletCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kEnemyBulletCollisionComponent.c_str();
}

bool rachet::PlayerEnemyBulletCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        out.target = target->GetOwner();
        auto pos = object->GetOwner()->GetPosition();
        auto target_pos = target->GetOwner()->GetPosition();
        out.angle.y = target->GetOwner()->GetRotate().y;
        out.speed = 30.0f;
        return true;
    } // if
    return false;
}