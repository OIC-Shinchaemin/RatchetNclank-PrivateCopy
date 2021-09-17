#include "ScarecrowBombGloveBulletCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::ScarecrowBombGloveBulletCollisionAlgolithm::ScarecrowBombGloveBulletCollisionAlgolithm() :
    super() {
}

ratchet::ScarecrowBombGloveBulletCollisionAlgolithm::~ScarecrowBombGloveBulletCollisionAlgolithm() {
}

const char* ratchet::ScarecrowBombGloveBulletCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kScarecrowCollisionComponent.c_str();
}

const char* ratchet::ScarecrowBombGloveBulletCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBombGloveBulletCollisionComponent.c_str();
}

bool ratchet::ScarecrowBombGloveBulletCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
    // 衝突オブジェクトを持っていないなら処理しない
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        out.target = target->GetOwner();
        return true;
    } // if
    return false;
}