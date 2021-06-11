#include "PyrocitorBullet.h"

#include "../../Component/VelocityComponent.h"


ratchet::PyrocitorBullet::PyrocitorBullet() :
    super() {
    _exist_time.Initialize(0.6f, false);
}

ratchet::PyrocitorBullet::~PyrocitorBullet() {
}

bool ratchet::PyrocitorBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<ratchet::VelocityComponent>();
    v->AddVelocityForce(_speed);
    
    super::Update(delta_time);
    return true;
}

bool ratchet::PyrocitorBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.2f), def::color_rgba::kRed);
    return true;
}

void ratchet::PyrocitorBullet::Start(const ratchet::PyrocitorBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<ratchet::VelocityComponent>();
    v ->SetGravity(0.0f);
}