#include "PlayerNanotechItemCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


ratchet::PlayerNanotechItemCollisionAlgolithm::PlayerNanotechItemCollisionAlgolithm() :
    super() {
}

ratchet::PlayerNanotechItemCollisionAlgolithm::~PlayerNanotechItemCollisionAlgolithm() {
}

const char* ratchet::PlayerNanotechItemCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* ratchet::PlayerNanotechItemCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::CollisionComponentType::kNanotechItemCollisionComponent.c_str();
}

bool ratchet::PlayerNanotechItemCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::CollisionComponent> object, std::shared_ptr<ratchet::CollisionComponent> target, ratchet::CollisionInfo& out) {
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