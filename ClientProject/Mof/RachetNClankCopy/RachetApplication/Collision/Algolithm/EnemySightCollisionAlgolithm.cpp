#include "EnemySightCollisionAlgolithm.h"

#include "My/Core/Math.h"


my::EnemySightPlayerCollisionAlgolithm::EnemySightPlayerCollisionAlgolithm() :
    super() {
}

my::EnemySightPlayerCollisionAlgolithm::~EnemySightPlayerCollisionAlgolithm() {
}

const char* my::EnemySightPlayerCollisionAlgolithm::GetLayerType(void) const {
    return "EnemySightCollisionObject";
}

const char* my::EnemySightPlayerCollisionAlgolithm::GetTargetType(void) const {
    return "PlayerCollisionObject";
}
/*
void my::EnemySightPlayerCollisionAlgolithm::Collision(std::shared_ptr<my::CollisionObject> object, std::shared_ptr<my::CollisionObject> target, const my::CollisionInfo& info) {
    object->ExcuteFunction("PlayerCollisionObject", info);
}
*/
bool my::EnemySightPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionObject> object, std::shared_ptr<my::CollisionObject> target, my::CollisionInfo& out) {
    // 衝突オブジェクトを持っていないなら処理しない
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (!object->GetSightObject().has_value()) {
        return false;
    } // if

    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        // 相手へのベクトルと自分の前方ベクトルの内積が正（>０）の場合は鋭角であり前方９０°以内と判断できる
        auto pos = object->GetSightObject().value().position;
        auto rotate = object->GetSightObject().value().rotate;

        Mof::CVector3 dir = target->GetSphere().value().Position - pos;
        Mof::CVector3 front(-math::vec3::kUnitZ);
        Mof::CMatrix33 mat;
        mat.RotationZXY(rotate);
        front *= mat;
        if (front.Dot(dir) > 0.0f) {
            out.target = target->GetOwner();
            return true;
        } // if
    } // if
    return false;
}