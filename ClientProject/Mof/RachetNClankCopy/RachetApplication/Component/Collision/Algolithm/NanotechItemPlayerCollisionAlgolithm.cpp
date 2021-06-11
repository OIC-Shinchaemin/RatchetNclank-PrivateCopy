#include "NanotechItemPlayerCollisionAlgolithm.h"

#include "../Object/CollisionComponentDefine.h"


rachet::NanotechItemPlayerCollisionAlgolithm::NanotechItemPlayerCollisionAlgolithm() :
    super() {
}

rachet::NanotechItemPlayerCollisionAlgolithm::~NanotechItemPlayerCollisionAlgolithm() {
}

const char* rachet::NanotechItemPlayerCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kNanotechItemCollisionComponent.c_str();
}

const char* rachet::NanotechItemPlayerCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool rachet::NanotechItemPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
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