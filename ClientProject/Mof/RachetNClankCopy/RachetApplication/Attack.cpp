#include "Attack.h"

#include "My/Core/Define.h"
#include "Character/Enemy.h"


bool my::Attack::InactiveCondition(void) const {
    //std::cout << "_motion->IsEndMotion() = " << _motion->IsEndMotion() << "\n";
    //return _motion->IsEndMotion();
    return false;
}

void my::Attack::Execute(float delta_time) {
}

my::Attack::Attack() :
    _range(2.0f),
    _volume(0.5f),
    _motion() {
}

my::Attack::~Attack() {
}

void my::Attack::SetMotion(Mof::LPMeshMotionController ptr) {
    this->_motion = ptr;
}

float my::Attack::GetRange(void) const {
    return this->_range;
}

float my::Attack::GetVolume(void) const {
    return this->_volume;
}

Mof::CSphere my::Attack::GetSphere(void) const {
    if (!this->IsActive()) {
        return Mof::CSphere();
    } // if
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

Mof::CSphere my::Attack::GetCanAttackRangeSphere(void) const {
    if (auto owner = _owner.lock()) {
        auto pos = owner->GetPosition();
        return Mof::CSphere(pos, _range);
    } // if
    return Mof::CSphere();
}

bool my::Attack::Start(void) {
    if (_active) {
        return false;
    } // if
    _active = true;
    super::GetOwner()->ChangeMotionState("EnemyMotionAttackState");
    return true;
}

void my::Attack::Inactive(void) {
    this->_active = false;
}

void my::Attack::RenderDebug(void) {
    ::CGraphicsUtilities::RenderLineSphere(this->GetSphere(), def::color_rgba::kMagenta);
    ::CGraphicsUtilities::RenderLineSphere(this->GetCanAttackRangeSphere(), def::color_rgba::kYellow);
}