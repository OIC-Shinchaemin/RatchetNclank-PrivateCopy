#include "PlayerWaterFlowCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


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
    return false;
}