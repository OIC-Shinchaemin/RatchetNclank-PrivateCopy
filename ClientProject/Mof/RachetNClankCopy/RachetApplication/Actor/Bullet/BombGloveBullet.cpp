#include "BombGloveBullet.h"

#include "../../Component/VelocityComponent.h"


rachet::BombGloveBullet::BombGloveBullet() :
    super() {
    _exist_time.Initialize(5.0f, false);
}

rachet::BombGloveBullet::~BombGloveBullet() {
}

float rachet::BombGloveBullet::GetGravity(void) const {
    return 0.25f;
}

float rachet::BombGloveBullet::GetDrag(void) const {
    return 1.0f;
}

bool rachet::BombGloveBullet::Update(float delta_time) {
    super::BulletUpdate(delta_time);

    auto v = super::GetComponent<rachet::VelocityComponent>();
    if (_speed.Length() > 0.001f) {
        v->AddVelocityForce(_speed);
        _speed = math::vec3::kZero;
    } // if

    super::Update(delta_time);
    return true;
}

bool rachet::BombGloveBullet::Render(void) {
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(super::GetPosition(), 0.2f), def::color_rgba::kBlue);
    return true;
}

void rachet::BombGloveBullet::Start(const rachet::BombGloveBullet::Param& in) {
    super::Start(in);
    auto v = super::GetComponent<rachet::VelocityComponent>();
    v->SetGravity(this->GetGravity());
    v->SetDrag(this->GetDrag());
    v->SetUseGravity(true);
}