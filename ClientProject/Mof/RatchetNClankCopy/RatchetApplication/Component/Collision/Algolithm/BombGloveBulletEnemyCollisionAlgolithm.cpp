#include "BombGloveBulletEnemyCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


ratchet::BombGloveBulletEnemyCollisionAlgolithm::BombGloveBulletEnemyCollisionAlgolithm() :
    super() {
}

ratchet::BombGloveBulletEnemyCollisionAlgolithm::~BombGloveBulletEnemyCollisionAlgolithm() {
}

const char* ratchet::BombGloveBulletEnemyCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBombGloveBulletCollisionComponent.c_str();
}

const char* ratchet::BombGloveBulletEnemyCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kEnemyCollisionComponent.c_str();
}

bool ratchet::BombGloveBulletEnemyCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
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