#include "BombGloveBulletEnemyCollisionAlgolithm.h"


my::BombGloveBulletEnemyCollisionAlgolithm::BombGloveBulletEnemyCollisionAlgolithm() :
    super() {
}

my::BombGloveBulletEnemyCollisionAlgolithm::~BombGloveBulletEnemyCollisionAlgolithm() {
}

const char* my::BombGloveBulletEnemyCollisionAlgolithm::GetLayerType(void) const {
    return "BombGloveBulletCollisionComponent";
}

const char* my::BombGloveBulletEnemyCollisionAlgolithm::GetTargetType(void) const {
    return "EnemyCollisionComponent";
}

bool my::BombGloveBulletEnemyCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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