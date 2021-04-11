#include "BombGlove.h"

#include "../../Gamepad.h"
#include "../../Actor/Bullet/BombGloveBullet.h"
#include "../../Actor/ParticleEffect.h"


my::BombGlove::BombGlove() :
    super() {
    super::SetName("BombGlove");
    super::_mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/bomb_glove/scene.mom");
    super::_shot_speed = 15.0f;
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
    auto add = ut::MakeSharedWithRelease<my::BombGloveBullet>();
    auto param = my::Bullet::Param();

    param.transform = transform;
    auto speed = Mof::CVector3(0.0f, 0.0f, -super::_shot_speed);
    speed.RotateAround(math::vec3::kZero, param.transform.rotate);
    param.speed = speed;
    param.speed.y = super::_shot_speed * 0.4f;

    add->Start(param);
    Observable::Notify("AddRequest", add);
    return true;
}