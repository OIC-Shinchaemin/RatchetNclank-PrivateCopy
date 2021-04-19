#include "PlayerEnemyAttackCollisionAlgolithm.h"

#include "My/Core/Math.h"


my::PlayerEnemyAttackCollisionAlgolithm::PlayerEnemyAttackCollisionAlgolithm() :
    super() {
}

my::PlayerEnemyAttackCollisionAlgolithm::~PlayerEnemyAttackCollisionAlgolithm() {
}

const char* my::PlayerEnemyAttackCollisionAlgolithm::GetLayerType(void) const {
    return "PlayerCollisionObject";
}

const char* my::PlayerEnemyAttackCollisionAlgolithm::GetTargetType(void) const {
    return "EnemyAttackCollisionObject";
}

bool my::PlayerEnemyAttackCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionObject> object, std::shared_ptr<my::CollisionObject> target, my::CollisionInfo& out) {
    // �Փ˃I�u�W�F�N�g�������Ă��Ȃ��Ȃ珈�����Ȃ�
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        out.target = target->GetOwner();
        auto pos = object->GetOwner()->GetPosition();
        auto target_pos = target->GetOwner()->GetPosition();
        //out.angle.y = std::atan2(pos.z - target_pos.z, pos.x - target_pos.x);
        out.angle.y = target->GetOwner()->GetRotate().y;
        return true;
    } // if
    return false;
}