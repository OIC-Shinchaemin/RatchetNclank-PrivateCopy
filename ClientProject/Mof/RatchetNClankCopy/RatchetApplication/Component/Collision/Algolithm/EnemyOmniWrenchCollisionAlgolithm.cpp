#include "EnemyOmniWrenchCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


ratchet::EnemyOmniWrenchCollisionAlgolithm::EnemyOmniWrenchCollisionAlgolithm() :
    super() {
}

ratchet::EnemyOmniWrenchCollisionAlgolithm::~EnemyOmniWrenchCollisionAlgolithm() {
}

const char* ratchet::EnemyOmniWrenchCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

const char* ratchet::EnemyOmniWrenchCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::CollisionComponentType::kOmniWrenchCollisionComponent.c_str();
}

bool ratchet::EnemyOmniWrenchCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::CollisionComponent> object, std::shared_ptr<ratchet::CollisionComponent> target, ratchet::CollisionInfo& out) {
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