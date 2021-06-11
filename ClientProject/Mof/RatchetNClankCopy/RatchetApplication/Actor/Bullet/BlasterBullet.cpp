#include "BlasterBullet.h"

#include "../../Component/VelocityComponent.h"


ratchet::BlasterBullet::BlasterBullet() :
    super() {
    super::SetTag("BlasterBullet");
    _exist_time.Initialize(1.2f,false);
}

ratchet::BlasterBullet::~BlasterBullet() {
}

bool ratchet::BlasterBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<ratchet::VelocityComponent>();
    v->AddVelocityForce(_speed);

    super::Update(delta_time);
    return true;
}

bool ratchet::BlasterBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.2f), def::color_rgba::kBlack);
    return true;
}

void ratchet::BlasterBullet::Start(const ratchet::BlasterBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<ratchet::VelocityComponent>();
    v ->SetGravity(0.0f);
}