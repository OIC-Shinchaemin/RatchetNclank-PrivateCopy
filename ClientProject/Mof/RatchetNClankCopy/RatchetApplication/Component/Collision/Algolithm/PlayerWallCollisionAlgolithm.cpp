#include "PlayerWallCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


ratchet::PlayerWallCollisionAlgolithm::PlayerWallCollisionAlgolithm() :
    super() {
}

ratchet::PlayerWallCollisionAlgolithm::~PlayerWallCollisionAlgolithm() {
}

const char* ratchet::PlayerWallCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* ratchet::PlayerWallCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kWallCollisionComponent.c_str();
}

bool ratchet::PlayerWallCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
    // 衝突オブジェクトを持っていないなら処理しない
    //if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
    if (!object->GetSphere().has_value() || !target->GetBox().has_value()) {
        return false;
    } // if
    
    auto box = target->GetBox().value();
    auto pos = Mof::CVector3(object->GetSphere().value().Position.x, 
                             object->GetSphere().value().Position.y, 
                             object->GetSphere().value().Position.z);
    if (box.CollisionPoint(pos)) {
        out.target = target->GetOwner();
        return true;
    } // if
    return false;
}