#include "Pyrocitor.h"

#include "../../Gamepad.h"
#include "../Bullet/PyrocitorBullet.h"
#include "../../Factory/FactoryManager.h"


ratchet::Pyrocitor::Pyrocitor() :
    super() {
    super::SetName("Pyrocitor");
    super::_shot_speed = 2.0f;
    super::_interval_max = 0.06f;
    super::_bullet_count_max = 240;
    super::_bullet_count = super::_bullet_count_max;
}

ratchet::Pyrocitor::~Pyrocitor() {
}

bool ratchet::Pyrocitor::IsAction(void) const {
    return ::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_B) || ::g_pInput->IsKeyHold(MOFKEY_M);
}

bool ratchet::Pyrocitor::Fire(const def::Transform& transform) {
    super::Fire(transform);
    auto param = ratchet::Bullet::Param();

    param.transform = transform;
    auto speed = Mof::CVector3(0.0f, 0.0f, -_shot_speed);
    speed.RotateAround(math::vec3::kZero, param.transform.rotate);
    param.speed = speed;
    param.speed.y = _shot_speed * 0.2f;

    auto add = ratchet::FactoryManager::Singleton().CreateActor<ratchet::PyrocitorBullet>("../Resource/builder/pyrocitor_bullet.json", &param);
    add->Start(param);
    Observable::Notify("AddRequest", add);
    return true;
}