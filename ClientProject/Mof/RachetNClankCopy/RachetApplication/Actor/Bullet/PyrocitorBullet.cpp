#include "PyrocitorBullet.h"

#include "../../Component/VelocityComponent.h"


rachet::PyrocitorBullet::PyrocitorBullet() :
    super() {
    _exist_time.Initialize(0.6f, false);
}

rachet::PyrocitorBullet::~PyrocitorBullet() {
}

bool rachet::PyrocitorBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<rachet::VelocityComponent>();
    v->AddVelocityForce(_speed);
    
    super::Update(delta_time);
    return true;
}

bool rachet::PyrocitorBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.2f), def::color_rgba::kRed);
    return true;
}

void rachet::PyrocitorBullet::Start(const rachet::PyrocitorBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<rachet::VelocityComponent>();
    v ->SetGravity(0.0f);
}