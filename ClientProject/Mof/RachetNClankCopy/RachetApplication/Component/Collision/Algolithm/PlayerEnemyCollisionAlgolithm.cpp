#include "PlayerEnemyCollisionAlgolithm.h"

#include "../../../Actor/Character/Enemy.h"


my::PlayerEnemyCollisionAlgolithm::PlayerEnemyCollisionAlgolithm() :
    super() {
}

my::PlayerEnemyCollisionAlgolithm::~PlayerEnemyCollisionAlgolithm() {
}

const char* my::PlayerEnemyCollisionAlgolithm::GetLayerType(void) const {
    return "PlayerCollisionComponent";
}

const char* my::PlayerEnemyCollisionAlgolithm::GetTargetType(void) const {
    return "EnemyCollisionComponent";
}
/*
void my::PlayerEnemyCollisionAlgolithm::Collision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, const my::CollisionInfo& info) {
    object->ExcuteFunction("EnemyCollisionComponent", info);
}
*/
bool my::PlayerEnemyCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
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