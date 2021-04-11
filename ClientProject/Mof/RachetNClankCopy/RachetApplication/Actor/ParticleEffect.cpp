#include "ParticleEffect.h"

#include "../Component/VelocityComponent.h"


my::ParticleEffect::ParticleEffect() :
    super(),
    _color(),
    _life_time(),
    _size(0.5f),
    _update_param(),
    _environment_param() {
}

my::ParticleEffect::~ParticleEffect() {
}

bool my::ParticleEffect::Update(float delta_time) {
    if (_life_time.Tick(delta_time)) {
        super::End();
    } // if

    auto v = super::GetComponent<my::VelocityComponent>();

    v ->AddVelocityForce(_update_param.velocity);
    v->AddAngularVelocityForce(_update_param.rotate);
    super::SetScale(super::GetScale() + _update_param.scale);
    _color += _update_param.color;

    super::Update(delta_time);
    return true;
}

bool my::ParticleEffect::Render(void) {
    auto pos = super::GetPosition();
    auto sphere = Mof::CSphere(super::GetPosition(), super::GetScale().Length());
    ::CGraphicsUtilities::RenderSphere(sphere, _color);
    return true;
}

void my::ParticleEffect::Start(const my::ParticleEffect::Info& info) {
    super::Initialize((super::Param*)(&info));
    if (!info.environment_param.gravity) {
        auto v = super::GetComponent<my::VelocityComponent>();

        v ->SetGravity(0.0f);
    } // if

    _update_param = info.update_param;
    _environment_param = info.environment_param;
    _color = info.init_param.color;

    _life_time.Initialize(info.init_param.life_time, false);
}