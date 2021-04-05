#include "BombGloveBullet.h"


my::BombGloveBullet::BombGloveBullet() :
    super() {
    super::_velocity.SetDrag(0.98f);
    super::_mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/blaster_bullet/scene.mom");
    super::_exist_time_max = 5.0f;
}

my::BombGloveBullet::~BombGloveBullet() {
}

bool my::BombGloveBullet::Update(float delta_time) {
    super::Update(delta_time);

    if (_speed.Length() > 0.001f) {
        _velocity.AddVelocityForce(_speed);
        _speed = math::vec3::kZero;
    } // if

    _velocity.Update(delta_time);
    super::UpdateTransform(delta_time);
    return true;
}

bool my::BombGloveBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.2f), def::color_rgba::kBlue);
    return true;
}

void my::BombGloveBullet::Start(const my::BombGloveBullet::Param& in) {
    super::Start(in);
}