#include "PlayerWaterFlowCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"
#include "../Object/PlayerCollisionComponent.h"
#include "../../Player/PlayerComponent.h"


ratchet::PlayerWaterFlowCollisionAlgolithm::PlayerWaterFlowCollisionAlgolithm() :
    super() {
}

ratchet::PlayerWaterFlowCollisionAlgolithm::~PlayerWaterFlowCollisionAlgolithm() {
}

const char* ratchet::PlayerWaterFlowCollisionAlgolithm::GetLayerType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* ratchet::PlayerWaterFlowCollisionAlgolithm::GetTargetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kWaterFlowCollisionComponent.c_str();
}

bool ratchet::PlayerWaterFlowCollisionAlgolithm::IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent> object, std::shared_ptr<ratchet::component::collision::CollisionComponent> target, component::collision::CollisionInfo& out) {
    // 衝突オブジェクトを持っていないなら処理しない
    if (!object->GetRay().has_value() || !target->GetPlaneObject().has_value()) {
        return false;
    } // if
    auto ray = object->GetRay().value();
    auto plane = target->GetPlaneObject().value();
    
    // 平面
    if (float distance; ray.CollisionPlane(plane.position, plane.normal, distance)) {
        if (auto com = object->GetOwner()->GetComponent<ratchet::component::player::PlayerComponent>(); com) {
            if (com->GetNextTerrain() != "Ground") {
                com->SetNextTerrain("WaterFlow");
            } // if
            return true;
        } // if
    } // if
    return false;
}