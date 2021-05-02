#include "EnemyBlasterBulletCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


my::EnemyBlasterBulletCollisionAlgolithm::EnemyBlasterBulletCollisionAlgolithm() :
    super() {
}

my::EnemyBlasterBulletCollisionAlgolithm::~EnemyBlasterBulletCollisionAlgolithm() {
}

const char* my::EnemyBlasterBulletCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

const char* my::EnemyBlasterBulletCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kBlasterBulletCollisionComponent.c_str();
}

bool my::EnemyBlasterBulletCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
    // 衝突オブジェクトを持っていないなら処理しない
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        out.target = target->GetOwner();
        
        auto target_pos = target->GetOwner()->GetPosition();
        Mof::CVector3 direction = target->GetOwner()->GetPosition() - target_pos;
        direction.Normal(direction);
        out.angle.y = direction.y;
        return true;
    } // if
    return false;
}