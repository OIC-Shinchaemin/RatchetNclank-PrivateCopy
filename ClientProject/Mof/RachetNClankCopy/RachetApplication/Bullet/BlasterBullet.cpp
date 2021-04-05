#include "BlasterBullet.h"


my::BlasterBullet::BlasterBullet() :
    super() {
    super::_mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/blaster_bullet/scene.mom");
    super::_exist_time_max = 3.0f;
}

my::BlasterBullet::~BlasterBullet() {
}

bool my::BlasterBullet::Update(float delta_time) {
    super::Update(delta_time);

    _velocity.AddVelocityForce(_speed);
    _velocity.Update(delta_time);
    super::UpdateTransform(delta_time);
    return true;
}

bool my::BlasterBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.2f), def::color_rgba::kBlack);
    return true;
}

void my::BlasterBullet::Start(const my::BlasterBullet::Param& in) {
    super::Start(in);
    super::_velocity.SetGravity(0.0f);
}