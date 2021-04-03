#include "EnemyCollisionAlgolithm.h"


my::EnemyPlayerCollisionAlgolithm::EnemyPlayerCollisionAlgolithm() :
    super() {
}

my::EnemyPlayerCollisionAlgolithm::~EnemyPlayerCollisionAlgolithm() {
}

const char* my::EnemyPlayerCollisionAlgolithm::GetLayerType(void) const {
    return "EnemyCollisionObject";
}

const char* my::EnemyPlayerCollisionAlgolithm::GetTargetType(void) const {
    return "PlayerCollisionObject";
}

void my::EnemyPlayerCollisionAlgolithm::Collision(std::shared_ptr<my::CollisionObject> object, std::shared_ptr<my::CollisionObject> target, const my::CollisionInfo& info) {
    object->ExcuteFunction("PlayerCollisionObject", info);
}

bool my::EnemyPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionObject> object, std::shared_ptr<my::CollisionObject> target, my::CollisionInfo& out) {
    // �Փ˃I�u�W�F�N�g�������Ă��Ȃ��Ȃ珈�����Ȃ�
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        return true;
    } // if
    return false;
}