#include "PlayerWaterFlowCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"
#include "../Object/PlayerCollisionComponent.h"
#include "../../Player/PlayerComponent.h"


rachet::PlayerWaterFlowCollisionAlgolithm::PlayerWaterFlowCollisionAlgolithm() :
    super() {
}

rachet::PlayerWaterFlowCollisionAlgolithm::~PlayerWaterFlowCollisionAlgolithm() {
}

const char* rachet::PlayerWaterFlowCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* rachet::PlayerWaterFlowCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kWaterFlowCollisionComponent.c_str();
}

bool rachet::PlayerWaterFlowCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
    // 衝突オブジェクトを持っていないなら処理しない
    if (!object->GetRay().has_value() || !target->GetPlaneObject().has_value()) {
        return false;
    } // if
    auto ray = object->GetRay().value();
    auto plane = target->GetPlaneObject().value();
    
    // 平面
    if (float distance; ray.CollisionPlane(plane.position, plane.normal, distance)) {
        if (auto com = object->GetOwner()->GetComponent<rachet::PlayerComponent>(); com) {
            if (com->GetNextTerrain() != "Ground") {
                com->SetNextTerrain("WaterFlow");
            } // if
            return true;
        } // if
    } // if
    return false;
}