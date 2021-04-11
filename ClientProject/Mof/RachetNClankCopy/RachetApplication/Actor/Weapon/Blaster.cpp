#include "Blaster.h"

#include "../../Gamepad.h"
#include "../../Actor/Bullet/BlasterBullet.h"
#include "../ParticleEffect.h"
#include "../../Factory/FactoryManager.h"


my::Blaster::Blaster() :
    super() {
    super::SetName("Blaster");
    //super::_mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/blaster/scene.mom");
    super::_shot_speed = 5.0f;
    super::_interval_max = 0.06f;
    super::_bullet_count = 200;
}

my::Blaster::~Blaster() {
}

bool my::Blaster::IsAction(void) const {
    return ::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_B) || ::g_pInput->IsKeyHold(MOFKEY_SPACE);
}

bool my::Blaster::Fire(const def::Transform& transform) {
    super::Fire(transform);
    auto param = my::Bullet::Param();
    
    param.transform = transform;
    auto speed = Mof::CVector3(0.0f, 0.0f, -_shot_speed);
    speed.RotateAround(math::vec3::kZero, param.transform.rotate);
    param.speed = speed;
    
    auto add = my::FactoryManager::Singleton().CreateActor<my::BlasterBullet>("../Resource/builder/blaster_bullet.json", &param);

    add->Start(param);
    Observable::Notify("AddRequest", add);

    /*
    {
        auto add = ut::MakeSharedWithRelease<my::BlasterBullet>();
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