#include "EnemyBlasterBulletCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


rachet::EnemyBlasterBulletCollisionAlgolithm::EnemyBlasterBulletCollisionAlgolithm() :
    super() {
}

rachet::EnemyBlasterBulletCollisionAlgolithm::~EnemyBlasterBulletCollisionAlgolithm() {
}

const char* rachet::EnemyBlasterBulletCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

const char* rachet::EnemyBlasterBulletCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kBlasterBulletCollisionComponent.c_str();
}

bool rachet::EnemyBlasterBulletCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
    // �Փ˃I�u�W�F�N�g�������Ă��Ȃ��Ȃ珈�����Ȃ�
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