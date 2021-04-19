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

    if (super::_lock_on_position.has_value()) {
        Mof::CVector3 direction =  super::_lock_on_position.value() - param.transform.position;
        direction.Normal(direction);
        param.speed = direction * _shot_speed;
        super::_lock_on_position.reset();
    } // if
    else {
        auto speed = Mof::CVector3(0.0f, 0.0f, -_shot_speed);
        speed.RotateAround(math::vec3::kZero, param.transform.rotate);
        param.speed = speed;
    } // else

    auto add = my::FactoryManager::Singleton().CreateActor<my::BlasterBullet>("../Resource/builder/blaster_bullet.json", &param);
    add->Start(param);
    Observable::Notify("AddRequest", add);
    return true;
}