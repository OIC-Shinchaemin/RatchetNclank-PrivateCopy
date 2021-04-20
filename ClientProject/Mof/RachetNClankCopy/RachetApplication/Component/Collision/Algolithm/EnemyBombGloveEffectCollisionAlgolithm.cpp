#include "EnemyBombGloveEffectCollisionAlgolithm.h"


my::EnemyBombGloveEffectCollisionAlgolithm::EnemyBombGloveEffectCollisionAlgolithm() :
    super() {
}

my::EnemyBombGloveEffectCollisionAlgolithm::~EnemyBombGloveEffectCollisionAlgolithm() {
}

const char* my::EnemyBombGloveEffectCollisionAlgolithm::GetLayerType(void) const {
    return "EnemyCollisionComponent";
}

const char* my::EnemyBombGloveEffectCollisionAlgolithm::GetTargetType(void) const {
    return "BombGloveEffectCollisionComponent";
}

bool my::EnemyBombGloveEffectCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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