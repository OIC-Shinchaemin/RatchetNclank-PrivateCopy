#include "EnemyOmniWrenchCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


my::EnemyOmniWrenchCollisionAlgolithm::EnemyOmniWrenchCollisionAlgolithm() :
    super() {
}

my::EnemyOmniWrenchCollisionAlgolithm::~EnemyOmniWrenchCollisionAlgolithm() {
}

const char* my::EnemyOmniWrenchCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

const char* my::EnemyOmniWrenchCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kOmniWrenchCollisionComponent.c_str();
}

bool my::EnemyOmniWrenchCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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