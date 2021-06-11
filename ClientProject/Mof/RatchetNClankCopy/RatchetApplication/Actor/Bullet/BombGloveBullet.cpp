#include "BombGloveBullet.h"

#include "../../Component/VelocityComponent.h"


ratchet::actor::bullet::BombGloveBullet::BombGloveBullet() :
    super() {
    _exist_time.Initialize(5.0f, false);
}

ratchet::actor::bullet::BombGloveBullet::~BombGloveBullet() {
}

float ratchet::actor::bullet::BombGloveBullet::GetGravity(void) const {
    return 0.25f;
}

float ratchet::actor::bullet::BombGloveBullet::GetDrag(void) const {
    return 1.0f;
}

bool ratchet::actor::bullet::BombGloveBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<ratchet::VelocityComponent>();
    if (_speed.Length() > 0.001f) {
        v->AddVelocityForce(_speed);
        _speed = math::vec3::kZero;
    } // if

    super::Update(delta_time);
    return true;
}

bool ratchet::actor::bullet::BombGloveBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.2f), def::color_rgba::kBlue);
    return true;
}

void ratchet::actor::bullet::BombGloveBullet::Start(const ratchet::actor::bullet::BombGloveBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<ratchet::VelocityComponent>();
    v->SetGravity(this->GetGravity());
    v->SetDrag(this->GetDrag());
    v->SetUseGravity(true);
}