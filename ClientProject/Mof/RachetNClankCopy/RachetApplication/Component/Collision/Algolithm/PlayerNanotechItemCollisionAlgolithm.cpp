#include "PlayerNanotechItemCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


my::PlayerNanotechItemCollisionAlgolithm::PlayerNanotechItemCollisionAlgolithm() :
    super() {
}

my::PlayerNanotechItemCollisionAlgolithm::~PlayerNanotechItemCollisionAlgolithm() {
}

const char* my::PlayerNanotechItemCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

const char* my::PlayerNanotechItemCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kNanotechItemCollisionComponent.c_str();
}

bool my::PlayerNanotechItemCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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