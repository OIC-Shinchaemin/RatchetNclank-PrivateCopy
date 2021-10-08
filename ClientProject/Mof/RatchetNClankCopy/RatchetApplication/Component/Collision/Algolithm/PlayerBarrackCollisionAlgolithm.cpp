#include "PlayerBarrackCollisionAlgolithm.h"

#include "../CollisionComponentDefine.h"


ratchet::PlayerBarrackCollisionAlgolithm::PlayerBarrackCollisionAlgolithm() :
    super() {
}

ratchet::PlayerBarrackCollisionAlgolithm::~PlayerBarrackCollisionAlgolithm() {
}

const char* ratchet::PlayerBarrackCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* ratchet::PlayerBarrackCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBarrackCollisionComponent.c_str();
}

bool ratchet::PlayerBarrackCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
        // 衝突オブジェクトを持っていないなら処理しない
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if

    auto object_sphere = object->GetSphere().value();
    auto object_ray = object->GetFrontRay().value();
    auto object_box = object->GetBox().value();
    auto target_box = target->GetBox().value();
    float distance = 0.0f;
    Mof::CVector3 pos = Mof::CVector3(object_sphere.x, object_sphere.y, object_sphere.z);

    if (object_box.CollisionAABB(target_box) &&
        object_ray.CollisionAABB(target_box, distance)) {
        out.target = target->GetOwner();
        out.distance = distance;
        return true;
    } // if

    return false;
}