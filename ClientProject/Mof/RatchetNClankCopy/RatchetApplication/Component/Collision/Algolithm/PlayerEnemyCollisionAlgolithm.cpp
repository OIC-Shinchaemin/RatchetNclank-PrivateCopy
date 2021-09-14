#include "PlayerEnemyCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::PlayerEnemyCollisionAlgolithm::PlayerEnemyCollisionAlgolithm() :
    super() {
}

ratchet::PlayerEnemyCollisionAlgolithm::~PlayerEnemyCollisionAlgolithm() {
}

const char* ratchet::PlayerEnemyCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* ratchet::PlayerEnemyCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

bool ratchet::PlayerEnemyCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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