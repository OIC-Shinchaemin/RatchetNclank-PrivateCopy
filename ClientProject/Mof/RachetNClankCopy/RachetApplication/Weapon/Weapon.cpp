#include "Weapon.h"

#include "../Bullet/Bullet.h"
#include "../ParticleEffect.h"


my::Weapon::Weapon() :
    super(),
    _mesh(){
}

my::Weapon::~Weapon() {
}

bool my::Weapon::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

bool my::Weapon::Render(void) {
    if (auto r = _mesh.lock()) {
        Mof::CMatrix44 scale, rotate, translate;
        scale.Scaling(super::GetScale(), scale);
        rotate.RotationZXY(super::GetRotate());
        translate.Translation(super::GetPosition(), translate);
        auto world = scale * rotate * translate;
        r->Render(world);
    } // if
    return false;
}

bool my::Weapon::Render(Mof::LPBONEMOTIONSTATE bone_state) {
    if (!bone_state) {
        return false;
    } // if 

    auto mat = bone_state->pBone->GetRotationOffsetMatrix() * bone_state->BoneMatrix;
    if (auto r = _mesh.lock()) {
        r->Render(mat);
    } // if
    return true;
}