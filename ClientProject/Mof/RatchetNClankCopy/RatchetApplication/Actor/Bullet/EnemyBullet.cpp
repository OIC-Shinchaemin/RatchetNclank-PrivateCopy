#include "EnemyBullet.h"

#include "../../Component/VelocityComponent.h"


ratchet::actor::bullet::EnemyBullet::EnemyBullet() :
    super() {
    _exist_time.Initialize(1.0f, false);
}

ratchet::actor::bullet::EnemyBullet::~EnemyBullet() {
}

bool ratchet::actor::bullet::EnemyBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<ratchet::VelocityComponent>();
    v->AddVelocityForce(_speed);
    
    super::Update(delta_time);
    return true;
}

bool ratchet::actor::bullet::EnemyBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.1f), def::color_rgba::kRed);
    return true;
}

void ratchet::actor::bullet::EnemyBullet::Start(const bullet::EnemyBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<ratchet::VelocityComponent>();
    v ->SetGravity(0.0f);
}