#include "EnemyBombGloveEffectCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


my::EnemyBombGloveEffectCollisionAlgolithm::EnemyBombGloveEffectCollisionAlgolithm() :
    super() {
}

my::EnemyBombGloveEffectCollisionAlgolithm::~EnemyBombGloveEffectCollisionAlgolithm() {
}

const char* my::EnemyBombGloveEffectCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kEnemyCollisionComponent.c_str();
//    return "EnemyCollisionComponent";
}

const char* my::EnemyBombGloveEffectCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kBombGloveEffectCollisionComponent.c_str();
}

bool my::EnemyBombGloveEffectCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
    // 衝突オブジェクトを持っていないなら処理しない
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        out.target = target->GetOwner();
        Mof::CVector3 direction = object->GetOwner()->GetPosition() - target->GetOwner()->GetPosition();
        out.angle.y = std::atan2(-direction.z, direction.x) + math::kHalfPi;
        out.speed = 60.0f;
        return true;
    } // if
    return false;
}