#include "Character.h"


my::Character::Character() :
    super(),
    _mesh(),
    _motion(),
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