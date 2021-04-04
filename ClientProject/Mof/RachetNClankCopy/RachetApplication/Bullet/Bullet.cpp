#include "Bullet.h"

void my::Bullet::UpdateTransform(float delta_time) {
    auto owner = this;
    // rotate
    auto rotate = this->UpdateRotate(delta_time, owner->GetRotate(), _velocity.GetAngularVelocity());
    owner->SetRotate(rotate);
    // position
    auto pos = this->UpdatePosition(delta_time, owner->GetPosition(), _velocity.GetVelocity());
    owner->SetPosition(pos);
}

my::Bullet::Bullet() :
    super(),
    _mesh(),
    _exist_time(0.0f),
    _speed(){
    _mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/blaster_bullet/scene.mom");
}

my::Bullet::~Bullet() {
}

bool my::Bullet::Update(float delta_time) {
    _exist_time += delta_time;
    if (5.0f <= _exist_time) {
        super::End();
    } // if

    _velocity.AddVelocityForce(_speed);
    _velocity.Update(delta_time);
    this->UpdateTransform(delta_time);
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


        ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.2f), def::color_rgba::kBlack);
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