#include "Bullet.h"


my::Bullet::Bullet() :
    super(),
    _speed(),
    _mesh(),
    _exist_time(0.0f),
    _exist_time_max(0.0f) {
}

my::Bullet::~Bullet() {
}

bool my::Bullet::Update(float delta_time) {
    _exist_time += delta_time;
    if (_exist_time_max <= _exist_time) {
        super::End();
    } // if
    return true;
}

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

void my::Bullet::Start(const my::Bullet::Param& in) {
    super::Initialize((super::Param*)(&in));
    _speed = in.speed;
}

void my::Bullet::RenderDebug(void) {
}