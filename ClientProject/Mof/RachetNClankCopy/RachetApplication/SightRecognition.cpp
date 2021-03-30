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
    _ASSERT_EXPR(!_owner.expired(),L"無効なポインタを参照しています");

    // 相手へのベクトルと自分の前方ベクトルの内積が正（>０）の場合は鋭角であり前方９０°以内と判断できる
    auto pos = _owner.lock()->GetPosition();
    auto rotate = _owner.lock()->GetRotate();

    Mof::CVector3 dir = target - pos;
    Mof::CVector3 front(-math::vec3::kUnitZ);
    Mof::CMatrix33 mat;
    mat.RotationZXY(rotate);
    front *= mat;
    if (front.Dot(dir) > 0.0f) {
        return true;
        /* 障害物無いなら見えるものとする
        _recognition.push_back(candidate);
        */
    } // if
    return false;
}