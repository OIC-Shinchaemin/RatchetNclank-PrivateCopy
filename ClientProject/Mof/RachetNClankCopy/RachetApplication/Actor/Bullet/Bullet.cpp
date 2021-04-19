#include "Bullet.h"


void my::Bullet::BulletUpdate(float delta_time) {
    if (_exist_time.Tick(delta_time)) {
        super::End();
    } // if
}

my::Bullet::Bullet() :
    super(),
    _speed(),
    _exist_time() {
}

my::Bullet::~Bullet() {
}

bool my::Bullet::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}
/*
bool my::Bullet::Render(void) {
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

bool my::Bullet::Release(void) {
    super::Release();
    return true;
}
*/

void my::Bullet::Start(const my::Bullet::Param& in) {
    super::Initialize((super::Param*)(&in));
    _speed = in.speed;
}