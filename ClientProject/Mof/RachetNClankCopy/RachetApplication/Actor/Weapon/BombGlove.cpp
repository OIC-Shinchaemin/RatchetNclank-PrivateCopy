#include "BombGlove.h"

#include "../../Gamepad.h"
#include "../../Actor/Bullet/BombGloveBullet.h"
#include "../../Factory/FactoryManager.h"


my::BombGlove::BombGlove() :
    super() {
    super::SetName("BombGlove");
    super::_shot_speed = 10.0f;
    super::_interval_max = 0.9f;
    super::_bullet_count = 40;
}

my::BombGlove::~BombGlove() {
}

bool my::BombGlove::IsAction(void) const {
    return ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_B) || ::g_pInput->IsKeyPush(MOFKEY_SPACE);
}

bool my::BombGlove::Fire(const def::Transform& transform) {
    super::Fire(transform);
    auto param = my::Bullet::Param();
    param.transform = transform;

    if (super::_lock_on_position.has_value()) {
        Mof::CVector3 direction = super::_lock_on_position.value() - param.transform.position;
        auto v = Mof::CVector3(direction.x, 0.0f, direction.z);
        float time = v.Length() / super::_shot_speed;

        float g = 0.25f * 60.0f;
        float v0 = 0.5f * g * time - direction.y;
        float v_t  = std::log10(0.98f * 60.0f * time) * super::_shot_speed;
        
        v.Normal(v);
        param.speed = v * v_t;
        param.speed.y = v0;
    } // if
    else {
        auto speed = Mof::CVector3(0.0f, 0.0f, -super::_shot_speed);
        speed.RotateAround(math::vec3::kZero, param.transform.rotate);
        param.speed = speed;
        param.speed.y = super::_shot_speed * 0.4f;
    } // else

    auto add = my::FactoryManager::Singleton().CreateActor<my::BombGloveBullet>("../Resource/builder/bomb_glove_bullet.json", &param);;
    add->Start(param);
    super::Observable::Notify("AddRequest", add);
    return true;
}