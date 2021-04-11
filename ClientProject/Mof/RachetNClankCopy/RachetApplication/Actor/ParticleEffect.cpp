#include "ParticleEffect.h"


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
    _life_time -= delta_time;
    if (_life_time <= 0.0f) {
        super::End();
    } // if

    super::_velocity.AddVelocityForce(_update_param.velocity);
    super::_velocity.AddAngularVelocityForce(_update_param.rotate);

    _velocity.Update(delta_time);
    super::SetScale(super::GetScale() + _update_param.scale);
    super::UpdateTransform(delta_time);
    _color += _update_param.color;
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
        super::_velocity.SetGravity(0.0f);
    } // if

    _update_param = info.update_param;
    _environment_param = info.environment_param;
    _life_time = info.init_param.life_time;
    _color = info.init_param.color;
}