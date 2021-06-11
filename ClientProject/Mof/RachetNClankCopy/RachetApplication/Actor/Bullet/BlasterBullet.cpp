#include "BlasterBullet.h"

#include "../../Component/VelocityComponent.h"


rachet::BlasterBullet::BlasterBullet() :
    super() {
    super::SetTag("BlasterBullet");
    _exist_time.Initialize(1.2f,false);
}

rachet::BlasterBullet::~BlasterBullet() {
}

bool rachet::BlasterBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<rachet::VelocityComponent>();
    v->AddVelocityForce(_speed);

    super::Update(delta_time);
    return true;
}

bool rachet::BlasterBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.2f), def::color_rgba::kBlack);
    return true;
}

void rachet::BlasterBullet::Start(const rachet::BlasterBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<rachet::VelocityComponent>();
    v ->SetGravity(0.0f);
}