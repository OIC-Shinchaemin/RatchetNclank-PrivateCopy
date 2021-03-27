#include "Weapon.h"

my::Weapon::Weapon() :
    super(),
    _mesh() {
    _mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/wrench/scene.mom");
}

my::Weapon::~Weapon() {
}

bool my::Weapon::Render(void) {
    super::SetPosition(Mof::CVector3(0.0f, 2.0f, 0.0f));
    super::SetScale(Mof::CVector3(1.0f, 1.0f, 1.0f));

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
