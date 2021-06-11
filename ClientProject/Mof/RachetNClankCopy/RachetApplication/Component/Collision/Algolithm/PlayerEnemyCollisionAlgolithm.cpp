#include "PlayerEnemyCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


rachet::PlayerEnemyCollisionAlgolithm::PlayerEnemyCollisionAlgolithm() :
    super() {
}

rachet::PlayerEnemyCollisionAlgolithm::~PlayerEnemyCollisionAlgolithm() {
}

const char* rachet::PlayerEnemyCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* rachet::PlayerEnemyCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

bool rachet::PlayerEnemyCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
    // 衝突オブジェクトを持っていないなら処理しない
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        out.target = target->GetOwner();
        return true;
    } // if
    return false;
}