#include "Character.h"



void my::Character::InputMoveVelocity(Mof::CVector2 stick, float speed) {
    // “ü—Í‘¬“x
    auto accele = Mof::CVector3(0.0f, 0.0f, -speed * stick.Length());
    auto rotate = super::GetRotate();
    accele.RotateAround(Mof::CVector3(), rotate);

    // ‘¬“x’Ç‰Á
    _velocity.AddVelocityForce(accele);
}

void my::Character::InputMoveAngularVelocity(Mof::CVector2 stick, float speed) {
    // “ü—ÍŠp“x
    auto rotate = super::GetRotate();

    float angle_y = std::atan2(-stick.y, stick.x) - math::kHalfPi;

    if (math::kTwoPi <= angle_y) {
        angle_y -= math::kTwoPi;
    } // if
    else if (angle_y <= 0.0f) {
        angle_y += math::kTwoPi;
    } // else if

    // ·•ªŠp“x
    angle_y -= rotate.y;
    if (math::kPi < angle_y) {
        angle_y -= math::kTwoPi;
    } // if
    else if (angle_y < -math::kPi) {
        angle_y += math::kTwoPi;
    } // else if

    auto accele = Mof::CVector3(0.0f, angle_y * speed, 0.0f);
    _velocity.AddAngularVelocityForce(accele);
}

void my::Character::UpdateTransform(float delta_time) {
    auto owner = this;
    // rotate
    auto rotate = this->UpdateRotate(delta_time, owner->GetRotate(), _velocity.GetAngularVelocity());
    owner->SetRotate(rotate);
    // position
    auto pos = this->UpdatePosition(delta_time, owner->GetPosition(), _velocity.GetVelocity());
    if (pos.y < 0.0f) {
        pos.y = 0.0f;
    } // if
    owner->SetPosition(pos);
}

my::Character::Character() :
    super(),
    _mesh(),
    _motion(),
    _velocity(),
    _volume(0.5f),
    _height(1.0f) {
}

my::Character::~Character() {
}

float my::Character::GetVolume(void) const {
    return this->_volume;
}

float my::Character::GetHeight(void) const {
    return this->_height;
}

Mof::CSphere my::Character::GetSphere(void) const {
    auto pos = super::GetPosition();
    pos.y += _height;
    return Mof::CSphere(pos, _volume);
}

bool my::Character::Initialize(my::Actor::Param* param) {
    super::Initialize(param);
    return true;
}

bool my::Character::Update(float delta_time) {
    _motion->AddTimer(delta_time);
    _velocity.Update(delta_time);
    return true;
}

bool my::Character::Render(void) {
    if (auto mesh = _mesh.lock()) {
        CMatrix44 matWorld;
        matWorld.RotationZXY(super::GetRotate());
        matWorld.SetTranslation(super::GetPosition());
        _motion->RefreshBoneMatrix(matWorld);
        mesh->Render(_motion);
    } // if
    return true;
}

bool my::Character::Release(void) {
    super::Release();

    _mesh.reset();
    ut::SafeDelete(_motion);
    return true;
}

void my::Character::RenderDebug(void) {
    ::CGraphicsUtilities::RenderLineSphere(this->GetSphere(), def::color_rgba::kRed);
}