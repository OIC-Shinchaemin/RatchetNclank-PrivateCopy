#include "ScarecrowBombGloveEffectCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::ScarecrowBombGloveEffectCollisionAlgolithm::ScarecrowBombGloveEffectCollisionAlgolithm() :
    super() {
}

ratchet::ScarecrowBombGloveEffectCollisionAlgolithm::~ScarecrowBombGloveEffectCollisionAlgolithm() {
}

const char* ratchet::ScarecrowBombGloveEffectCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kScarecrowCollisionComponent.c_str();
}

const char* ratchet::ScarecrowBombGloveEffectCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBombGloveEffectCollisionComponent.c_str();
}

bool ratchet::ScarecrowBombGloveEffectCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
    // 衝突オブジェクトを持っていないなら処理しない
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        out.target = target->GetOwner();
        Mof::CVector3 direction = object->GetOwner()->GetPosition() - target->GetOwner()->GetPosition();
        out.angle.y = std::atan2(-direction.z, direction.x) + math::kHalfPi;
        out.speed = 60.0f;
        return true;
    } // if
    return false;
}