#include "BombGloveBullet.h"

#include "../../Component/VelocityComponent.h"


ratchet::BombGloveBullet::BombGloveBullet() :
    super() {
    _exist_time.Initialize(5.0f, false);
}

ratchet::BombGloveBullet::~BombGloveBullet() {
}

float ratchet::BombGloveBullet::GetGravity(void) const {
    return 0.25f;
}

float ratchet::BombGloveBullet::GetDrag(void) const {
    return 1.0f;
}

bool ratchet::BombGloveBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<ratchet::VelocityComponent>();
    if (_speed.Length() > 0.001f) {
        v->AddVelocityForce(_speed);
        _speed = math::vec3::kZero;
    } // if

    super::Update(delta_time);
    return true;
}

bool ratchet::BombGloveBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.2f), def::color_rgba::kBlue);
    return true;
}

void ratchet::BombGloveBullet::Start(const ratchet::BombGloveBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<ratchet::VelocityComponent>();
    v->SetGravity(this->GetGravity());
    v->SetDrag(this->GetDrag());
    v->SetUseGravity(true);
}