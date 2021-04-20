#include "EnemyPyrocitorBulletCollisionAlgolithm.h"


my::EnemyPyrocitorBulletCollisionAlgolithm::EnemyPyrocitorBulletCollisionAlgolithm() :
    super() {
}

my::EnemyPyrocitorBulletCollisionAlgolithm::~EnemyPyrocitorBulletCollisionAlgolithm() {
}

const char* my::EnemyPyrocitorBulletCollisionAlgolithm::GetLayerType(void) const {
    return "EnemyCollisionComponent";
}

const char* my::EnemyPyrocitorBulletCollisionAlgolithm::GetTargetType(void) const {
    return "PyrocitorBulletCollisionComponent";
}

bool my::EnemyPyrocitorBulletCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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