#include "Character.h"


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
    _volume(1.0f),
    _height(1.0f) {
}

my::Character::~Character() {
}

Mof::CSphere my::Character::GetSphere(void) const {
    return Mof::CSphere(super::GetPosition(), _volume);
}

bool my::Character::Initialize(const def::Transform& transform) {
    super::Initialize(transform);
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