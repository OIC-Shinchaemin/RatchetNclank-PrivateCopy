#include "EnemySightPlayerCollisionAlgolithm.h"

#include "My/Core/Math.h"


my::EnemySightPlayerCollisionAlgolithm::EnemySightPlayerCollisionAlgolithm() :
    super() {
}

my::EnemySightPlayerCollisionAlgolithm::~EnemySightPlayerCollisionAlgolithm() {
}

const char* my::EnemySightPlayerCollisionAlgolithm::GetLayerType(void) const {
    return "EnemySightCollisionComponent";
}

const char* my::EnemySightPlayerCollisionAlgolithm::GetTargetType(void) const {
    return "PlayerCollisionComponent";
}

bool my::EnemySightPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<my::CollisionComponent> object, std::shared_ptr<my::CollisionComponent> target, my::CollisionInfo& out) {
    // �Փ˃I�u�W�F�N�g�������Ă��Ȃ��Ȃ珈�����Ȃ�
    if (!object->GetSphere().has_value() || !target->GetSphere().has_value()) {
        return false;
    } // if
    if (!object->GetSightObject().has_value()) {
        return false;
    } // if

    if (object->GetSphere().value().CollisionSphere(target->GetSphere().value())) {
        // ����ւ̃x�N�g���Ǝ����̑O���x�N�g���̓��ς����i>�O�j�̏ꍇ�͉s�p�ł���O���X�O���ȓ��Ɣ��f�ł���
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