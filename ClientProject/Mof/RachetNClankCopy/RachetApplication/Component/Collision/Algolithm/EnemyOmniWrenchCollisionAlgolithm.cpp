#include "EnemyOmniWrenchCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


rachet::EnemyOmniWrenchCollisionAlgolithm::EnemyOmniWrenchCollisionAlgolithm() :
    super() {
}

rachet::EnemyOmniWrenchCollisionAlgolithm::~EnemyOmniWrenchCollisionAlgolithm() {
}

const char* rachet::EnemyOmniWrenchCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

const char* rachet::EnemyOmniWrenchCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kOmniWrenchCollisionComponent.c_str();
}

bool rachet::EnemyOmniWrenchCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
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