#include "SightRecognition.h"

#include "Character/Enemy.h"


my::SightRecognition::SightRecognition() :
    _owner(),
    _range(5.0f) {
}

my::SightRecognition::~SightRecognition() {
}

void my::SightRecognition::SetOwner(const std::shared_ptr<my::Enemy>& owner) {
    this->_owner = owner;
}

float my::SightRecognition::GetRange(void) const {
    return this->_range;
}

bool my::SightRecognition::ContainInRecognitionRange(Mof::CVector3 target) {
    _ASSERT_EXPR(!_owner.expired(),L"�����ȃ|�C���^���Q�Ƃ��Ă��܂�");

    // ����ւ̃x�N�g���Ǝ����̑O���x�N�g���̓��ς����i>�O�j�̏ꍇ�͉s�p�ł���O���X�O���ȓ��Ɣ��f�ł���
    auto pos = _owner.lock()->GetPosition();
    auto rotate = _owner.lock()->GetRotate();

    Mof::CVector3 dir = target - pos;
    Mof::CVector3 front(-math::vec3::kUnitZ);
    Mof::CMatrix33 mat;
    mat.RotationZXY(rotate);
    front *= mat;
    if (front.Dot(dir) > 0.0f) {
        return true;
        /* ��Q�������Ȃ猩������̂Ƃ���
        _recognition.push_back(candidate);
        */
    } // if
    return false;
}