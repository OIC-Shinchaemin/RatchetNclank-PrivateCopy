#include "EnemyBullet.h"

#include "../../Component/VelocityComponent.h"


rachet::EnemyBullet::EnemyBullet() :
    super() {
    _exist_time.Initialize(1.0f, false);
}

rachet::EnemyBullet::~EnemyBullet() {
}

bool rachet::EnemyBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<rachet::VelocityComponent>();
    v->AddVelocityForce(_speed);
    
    super::Update(delta_time);
    return true;
}

bool rachet::EnemyBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.1f), def::color_rgba::kRed);
    return true;
}

void rachet::EnemyBullet::Start(const rachet::EnemyBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<rachet::VelocityComponent>();
    v ->SetGravity(0.0f);
}