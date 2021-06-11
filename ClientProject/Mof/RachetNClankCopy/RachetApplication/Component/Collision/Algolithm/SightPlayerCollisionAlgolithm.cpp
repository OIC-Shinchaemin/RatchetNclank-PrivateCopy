#include "SightPlayerCollisionAlgolithm.h"

#include "Base/Core/Math.h"
#include "../Object/CollisionComponentDefine.h"


rachet::SightPlayerCollisionAlgolithm::SightPlayerCollisionAlgolithm() :
    super() {
}

rachet::SightPlayerCollisionAlgolithm::~SightPlayerCollisionAlgolithm() {
}

const char* rachet::SightPlayerCollisionAlgolithm::GetLayerType(void) const {
    return rachet::CollisionComponentType::kSightCollisionComponent.c_str();
}

const char* rachet::SightPlayerCollisionAlgolithm::GetTargetType(void) const {
    return rachet::CollisionComponentType::kPlayerCollisionComponent.c_str();
}

bool rachet::SightPlayerCollisionAlgolithm::IsCollision(std::shared_ptr<rachet::CollisionComponent> object, std::shared_ptr<rachet::CollisionComponent> target, rachet::CollisionInfo& out) {
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