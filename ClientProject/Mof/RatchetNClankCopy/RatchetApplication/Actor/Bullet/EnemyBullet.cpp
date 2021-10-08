#include "EnemyBullet.h"

#include "../../Component/VelocityComponent.h"


ratchet::actor::bullet::EnemyBullet::EnemyBullet() :
    super(),
    _scale_multiply(0.99f),
    _scale_threshold(0.1) {
    _exist_time.Initialize(2.0f, false);
}

ratchet::actor::bullet::EnemyBullet::~EnemyBullet() {
}

bool ratchet::actor::bullet::EnemyBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<ratchet::component::VelocityComponent>();
    v->AddVelocityForce(_speed);

    auto scale = super::GetScale();
    scale *= _scale_multiply;
    super::SetScale(scale);
    if (scale.x < _scale_threshold) {
        super::End();
    } // if


    super::Update(delta_time);
    return true;
}

bool ratchet::actor::bullet::EnemyBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(
        super::GetPosition(),
        super::GetScale().x),
        def::color_rgba::kRed);
    return true;
}

void ratchet::actor::bullet::EnemyBullet::Start(const bullet::EnemyBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<ratchet::component::VelocityComponent>();
    v->SetGravity(0.0f);
}