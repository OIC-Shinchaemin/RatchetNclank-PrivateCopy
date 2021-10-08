#include "Pyrocitor.h"

#include "../../Gamepad.h"
#include "../Bullet/PyrocitorBullet.h"
#include "../../Factory/FactoryManager.h"


ratchet::actor::weapon::Pyrocitor::Pyrocitor() :
    super() {
    super::SetName("Pyrocitor");
    super::_shot_speed = 2.0f;
    super::_interval_max = 0.06f;
    super::_bullet_count_max = 240;
    super::_bullet_count = super::_bullet_count_max;
}

ratchet::actor::weapon::Pyrocitor::~Pyrocitor() {
}

bool ratchet::actor::weapon::Pyrocitor::IsAction(void) const {
    return ::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_B) || ::g_pInput->IsKeyHold(MOFKEY_V);
}

bool ratchet::actor::weapon::Pyrocitor::Fire(const def::Transform& transform) {
    super::Fire(transform);
    auto param = ratchet::actor::bullet::Bullet::Param();

    param.transform = transform;
    auto speed = Mof::CVector3(0.0f, 0.0f, -_shot_speed);
    speed.RotateAround(math::vec3::kZero, param.transform.rotate);
    param.speed = speed;
    param.speed.y = _shot_speed * 0.2f;

    auto add = ratchet::factory::FactoryManager::Singleton().
        CreateActor<ratchet::actor::bullet::PyrocitorBullet>
        ("../Resource/builder/pyrocitor_bullet.json", &param);
    add->Start(param);
    Observable::Notify("AddRequest", add);
    return true;
}