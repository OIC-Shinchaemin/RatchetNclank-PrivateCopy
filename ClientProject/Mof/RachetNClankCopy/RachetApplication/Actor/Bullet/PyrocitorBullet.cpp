#include "PyrocitorBullet.h"

#include "../../Component/VelocityComponent.h"


my::PyrocitorBullet::PyrocitorBullet() :
    super() {
    _exist_time.Initialize(0.6f, false);
}

my::PyrocitorBullet::~PyrocitorBullet() {
}

bool my::PyrocitorBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<my::VelocityComponent>();
    v->AddVelocityForce(_speed);
    
    super::Update(delta_time);
    return true;
}

bool my::PyrocitorBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.2f), def::color_rgba::kRed);
    return true;
}

void my::PyrocitorBullet::Start(const my::PyrocitorBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<my::VelocityComponent>();
    v ->SetGravity(0.0f);
}