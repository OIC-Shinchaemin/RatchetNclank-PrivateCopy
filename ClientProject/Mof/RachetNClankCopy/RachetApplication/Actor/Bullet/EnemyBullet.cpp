#include "EnemyBullet.h"

#include "../../Component/VelocityComponent.h"


ratchet::EnemyBullet::EnemyBullet() :
    super() {
    _exist_time.Initialize(1.0f, false);
}

ratchet::EnemyBullet::~EnemyBullet() {
}

bool ratchet::EnemyBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<ratchet::VelocityComponent>();
    v->AddVelocityForce(_speed);
    
    super::Update(delta_time);
    return true;
}

bool ratchet::EnemyBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.1f), def::color_rgba::kRed);
    return true;
}

void ratchet::EnemyBullet::Start(const ratchet::EnemyBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<ratchet::VelocityComponent>();
    v ->SetGravity(0.0f);
}