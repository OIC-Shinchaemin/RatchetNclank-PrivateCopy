#include "BlasterBullet.h"

#include "../../Component/VelocityComponent.h"


ratchet::actor::bullet::BlasterBullet::BlasterBullet() :
    super() {
    super::SetTag("BlasterBullet");
    _exist_time.Initialize(2.0f,false);
}

ratchet::actor::bullet::BlasterBullet::~BlasterBullet() {
}

bool ratchet::actor::bullet::BlasterBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<ratchet::component::VelocityComponent>();
    v->AddVelocityForce(_speed);

    super::Update(delta_time);
    return true;
}

bool ratchet::actor::bullet::BlasterBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), super::GetScale().x), def::color_rgba::kBlack);
    return true;
}

void ratchet::actor::bullet::BlasterBullet::Start(const ratchet::actor::bullet::BlasterBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<ratchet::component::VelocityComponent>();
    v ->SetGravity(0.0f);
}