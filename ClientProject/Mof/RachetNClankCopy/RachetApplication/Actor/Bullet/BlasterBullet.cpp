#include "BlasterBullet.h"

#include "../../Component/VelocityComponent.h"


my::BlasterBullet::BlasterBullet() :
    super() {
    super::SetTag("BlasterBullet");
    _exist_time.Initialize(1.2f,false);
}

my::BlasterBullet::~BlasterBullet() {
}

bool my::BlasterBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<my::VelocityComponent>();
    v->AddVelocityForce(_speed);

    super::Update(delta_time);
    return true;
}

bool my::BlasterBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.2f), def::color_rgba::kBlack);
    return true;
}

void my::BlasterBullet::Start(const my::BlasterBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<my::VelocityComponent>();
    v ->SetGravity(0.0f);
}