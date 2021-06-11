#include "PyrocitorBullet.h"

#include "../../Component/VelocityComponent.h"


ratchet::actor::bullet::PyrocitorBullet::PyrocitorBullet() :
    super() {
    _exist_time.Initialize(0.6f, false);
}

ratchet::actor::bullet::PyrocitorBullet::~PyrocitorBullet() {
}

bool ratchet::actor::bullet::PyrocitorBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<ratchet::VelocityComponent>();
    v->AddVelocityForce(_speed);
    
    super::Update(delta_time);
    return true;
}

bool ratchet::actor::bullet::PyrocitorBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.2f), def::color_rgba::kRed);
    return true;
}

void ratchet::actor::bullet::PyrocitorBullet::Start(const ratchet::actor::bullet::PyrocitorBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<ratchet::VelocityComponent>();
    v ->SetGravity(0.0f);
}