#include "NanotechItemPlayerCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


my::NanotechItemPlayerCollisionAlgolithm::NanotechItemPlayerCollisionAlgolithm() :
    super() {
}

my::NanotechItemPlayerCollisionAlgolithm::~NanotechItemPlayerCollisionAlgolithm() {
}

const char* my::NanotechItemPlayerCollisionAlgolithm::GetLayerType(void) const {
    return my::CollisionComponentType::kNanotechItemCollisionComponent.c_str();
}

const char* my::NanotechItemPlayerCollisionAlgolithm::GetTargetType(void) const {
    return my::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool my::NanotechItemPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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