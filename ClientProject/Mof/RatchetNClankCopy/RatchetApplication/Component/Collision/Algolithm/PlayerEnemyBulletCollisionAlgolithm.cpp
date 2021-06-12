#include "PlayerEnemyBulletCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


ratchet::PlayerEnemyBulletCollisionAlgolithm::PlayerEnemyBulletCollisionAlgolithm() :
    super() {
}

ratchet::PlayerEnemyBulletCollisionAlgolithm::~PlayerEnemyBulletCollisionAlgolithm() {
}

const char* ratchet::PlayerEnemyBulletCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* ratchet::PlayerEnemyBulletCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kEnemyBulletCollisionComponent.c_str();
}

bool ratchet::PlayerEnemyBulletCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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