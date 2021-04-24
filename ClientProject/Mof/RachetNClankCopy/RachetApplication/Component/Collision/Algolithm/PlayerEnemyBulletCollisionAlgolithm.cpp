#include "PlayerEnemyBulletCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


my::PlayerEnemyBulletCollisionAlgolithm::PlayerEnemyBulletCollisionAlgolithm() :
    super() {
}

my::PlayerEnemyBulletCollisionAlgolithm::~PlayerEnemyBulletCollisionAlgolithm() {
}

const char* my::PlayerEnemyBulletCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* my::PlayerEnemyBulletCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kEnemyBulletCollisionComponent.c_str();
}

bool my::PlayerEnemyBulletCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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