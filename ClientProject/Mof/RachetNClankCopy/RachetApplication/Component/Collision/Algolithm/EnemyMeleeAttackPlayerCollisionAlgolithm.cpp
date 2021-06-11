#include "EnemyMeleeAttackPlayerCollisionAlgolithm.h"

#include "Base/Core/Math.h"
#include "../Object/CollisionComponentDefine.h"


ratchet::EnemyMeleeAttackPlayerCollisionAlgolithm::EnemyMeleeAttackPlayerCollisionAlgolithm() :
    super() {
}

ratchet::EnemyMeleeAttackPlayerCollisionAlgolithm::~EnemyMeleeAttackPlayerCollisionAlgolithm() {
}

const char* ratchet::EnemyMeleeAttackPlayerCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::CollisionComponentType::kEnemyMeleeAttackCollisionComponent.c_str();
}

const char* ratchet::EnemyMeleeAttackPlayerCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool ratchet::EnemyMeleeAttackPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::CollisionComponent> object, std::shared_ptr<ratchet::CollisionComponent> target, ratchet::CollisionInfo& out) {
    // �Փ˃I�u�W�F�N�g�������Ă��Ȃ��Ȃ珈�����Ȃ�
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        out.target = target->GetOwner();
        return true;
    } // if
    return false;
}