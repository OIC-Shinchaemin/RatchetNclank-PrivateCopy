#include "PlayerWaterFlowCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"
#include "../Object/PlayerCollisionComponent.h"
#include "../../Player/PlayerComponent.h"


my::PlayerWaterFlowCollisionAlgolithm::PlayerWaterFlowCollisionAlgolithm() :
    super() {
}

my::PlayerWaterFlowCollisionAlgolithm::~PlayerWaterFlowCollisionAlgolithm() {
}

const char* my::PlayerWaterFlowCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* my::PlayerWaterFlowCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kWaterFlowCollisionComponent.c_str();
}

bool my::PlayerWaterFlowCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
    // 衝突オブジェクトを持っていないなら処理しない
    if (!object->GetRay().has_value() || !target->GetPlaneObject().has_value()) {
        return false;
    } // if
    auto ray = object->GetRay().value();
    auto plane = target->GetPlaneObject().value();
    
    // 平面
    if (float distance; ray.CollisionPlane(plane.position, plane.normal, distance)) {
        if (auto com = object->GetOwner()->GetComponent<my::PlayerComponent>(); com) {
            if (com->GetNextTerrain() != "Ground") {
                com->SetNextTerrain("WaterFlow");
            } // if
            return true;
        } // if
    } // if
    return false;
}