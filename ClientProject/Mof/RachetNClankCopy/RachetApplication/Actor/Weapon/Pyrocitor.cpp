#include "Pyrocitor.h"

#include "../../Gamepad.h"
#include "../Bullet/PyrocitorBullet.h"
#include "../ParticleEffect.h"


my::Pyrocitor::Pyrocitor() :
    super() {
    super::SetName("Pyrocitor");
    super::_mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/pyrocitor/scene.mom");
    super::_shot_speed = 2.0f;
    super::_interval_max = 0.06f;
    super::_bullet_count = 240;
}

my::Pyrocitor::~Pyrocitor() {
}

bool my::Pyrocitor::IsAction(void) const {
    return ::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_B) || ::g_pInput->IsKeyHold(MOFKEY_SPACE);
}

bool my::Pyrocitor::Fire(const def::Transform& transform) {
    super::Fire(transform);
    auto add = ut::MakeSharedWithRelease<my::PyrocitorBullet>();
    auto param = my::Bullet::Param();

    param.transform = transform;
    auto speed = Mof::CVector3(0.0f, 0.0f, -_shot_speed);
    speed.RotateAround(math::vec3::kZero, param.transform.rotate);
    param.speed = speed;
    param.speed.y = _shot_speed * 0.2f;

    add->Start(param);
    Observable::Notify("AddRequest", add);

    /*
    {
        auto add = ut::MakeSharedWithRelease<my::PyrocitorBullet>();
        auto param = my::Bullet::Param();
        param.transform = transform;
        auto speed = Mof::CVector3(0.0f, 0.0f, -_shot_speed);
        speed.RotateAround(math::vec3::kZero, param.transform.rotate);
        param.speed = speed;

        add->Start(param);
        Observable::Notify("AddRequest", add);
    }
    {
        auto add = ut::MakeSharedWithRelease<my::ParticleEffect>();
        Observable::Notify("AddRequest", add);
        auto param = my::ParticleEffect::Param();
        auto update_param = my::ParticleEffect::UpdateParam();
        param.transform.position = transform.position;
        param.transform.scale = Mof::CVector3(0.1f, 0.1f, 0.1f);
        param.color = def::color_rgba::kRed;
        param.life_time = 0.8f;

        auto speed = Mof::CVector3(0.0f, 0.0f, -_shot_speed * 0.25f);
        speed.RotateAround(math::vec3::kZero, transform.rotate);
        speed.y = 0.02f;
        update_param.velocity = speed;
        update_param.scale = Mof::CVector3(0.001f, 0.001f, 0.001f);

        auto info = my::ParticleEffect::Info();
        info.init_param = std::move(param);
        info.update_param = std::move(update_param);
        add->Start(info);
    }
    */
    return true;
}