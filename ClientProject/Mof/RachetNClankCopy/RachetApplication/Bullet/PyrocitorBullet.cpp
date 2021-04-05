#include "PyrocitorBullet.h"


my::PyrocitorBullet::PyrocitorBullet() :
    super() {
    super::_mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/blaster_bullet/scene.mom");
    super::_exist_time_max = 0.6f;
}

my::PyrocitorBullet::~PyrocitorBullet() {
}

bool my::PyrocitorBullet::Update(float delta_time) {
    super::Update(delta_time);

    _velocity.AddVelocityForce(_speed);
    _velocity.Update(delta_time);
    super::UpdateTransform(delta_time);
    return true;
}

bool my::PyrocitorBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.2f), def::color_rgba::kRed);
    return true;
}

void my::PyrocitorBullet::Start(const my::PyrocitorBullet::Param& in) {
    super::Start(in);
    super::_velocity.SetGravity(0.0f);
}