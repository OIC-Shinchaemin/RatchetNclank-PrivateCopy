#include "EnemyBullet.h"

#include "../../Component/VelocityComponent.h"


my::EnemyBullet::EnemyBullet() :
    super() {
    _exist_time.Initialize(1.0f, false);
}

my::EnemyBullet::~EnemyBullet() {
}

bool my::EnemyBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<my::VelocityComponent>();
    v->AddVelocityForce(_speed);
    
    super::Update(delta_time);
    return true;
}

bool my::EnemyBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.1f), def::color_rgba::kRed);
    return true;
}

void my::EnemyBullet::Start(const my::EnemyBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<my::VelocityComponent>();
    v ->SetGravity(0.0f);
}