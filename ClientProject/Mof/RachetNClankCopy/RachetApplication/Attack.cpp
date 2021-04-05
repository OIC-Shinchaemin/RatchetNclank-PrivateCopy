#include "Attack.h"

#include "My/Core/Define.h"
#include "Character/Enemy.h"


my::Attack::Attack() :
    _owner(),
    _range(2.0f),
    _volume(0.5f){
}

my::Attack::~Attack() {
}

void my::Attack::SetOwner(const std::shared_ptr<my::Enemy>& owner) {
    this->_owner = owner;
}

float my::Attack::GetRange(void) const {
    return this->_range;
}

float my::Attack::GetVolume(void) const {
    return this->_volume;
}

Mof::CSphere my::Attack::GetSphere(void) const {
    if (auto owner = _owner.lock()) {
        auto pos = owner->GetPosition();
        auto rotate = owner->GetRotate();

        float offset = 1.0f;
        auto front = Mof::CVector3(-math::vec3::kUnitZ * offset);
        front.RotationY(rotate.y);

        pos += front;
        pos.y += 1.0f;

        return Mof::CSphere(pos, _volume);
    } // if
    return Mof::CSphere();
}

Mof::CSphere my::Attack::GetRangeSphere(void) const {
    if (auto owner = _owner.lock()) {
        auto pos = owner->GetPosition();
        return Mof::CSphere(pos, _range);
    } // if
    return Mof::CSphere();
}

void my::Attack::Start(void) {
    if (auto owner = _owner.lock()) {
        owner->ChangeToAttackState();
    } // if
}

void my::Attack::RenderDebug(void) {
    ::CGraphicsUtilities::RenderLineSphere(this->GetSphere(), def::color_rgba::kMagenta);
    ::CGraphicsUtilities::RenderLineSphere(this->GetRangeSphere(), def::color_rgba::kYellow);
}