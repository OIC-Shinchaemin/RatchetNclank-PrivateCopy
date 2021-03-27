#include "Weapon.h"

my::Weapon::Weapon() :
    super(),
    _mesh() {
}

my::Weapon::~Weapon() {
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
