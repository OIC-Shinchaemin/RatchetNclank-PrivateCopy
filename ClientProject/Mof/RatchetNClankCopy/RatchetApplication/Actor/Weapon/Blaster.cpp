#include "Blaster.h"

#include "../../Gamepad.h"
#include "../../Actor/Bullet/BlasterBullet.h"
#include "../../Factory/FactoryManager.h"


ratchet::actor::weapon::Blaster::Blaster() :
    super(),
    _bullet_scale(0.3f),
    _scaling_maltiply(1.05f),
    _scaling(false) {
    super::SetName("Blaster");
    super::_shot_speed = 5.0f;
    super::_interval_max = 0.06f;
    super::_bullet_count_max = 200;
    super::_bullet_count = super::_bullet_count_max;
}

ratchet::actor::weapon::Blaster::~Blaster() {
}

bool ratchet::actor::weapon::Blaster::IsAction(void) const {
    return ::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_B) || ::g_pInput->IsKeyHold(MOFKEY_V);
}

bool ratchet::actor::weapon::Blaster::Update(float delta_time) {
    super::Update(delta_time);

    if (_scaling) {
        auto scale = super::GetScale();
        scale *= _scaling_maltiply;

        scale.x = std::clamp(scale.x, 0.0f, 1.0f);
        scale.y = std::clamp(scale.y, 0.0f, 1.0f);
        scale.z = std::clamp(scale.z, 0.0f, 1.0f);

        super::SetScale(scale);
        if (scale.x >= 1.0f ||
            scale.y >= 1.0f ||
            scale.z >= 1.0f) {
            _scaling = false;
        } // if
    } // if

    return true;
}

bool ratchet::actor::weapon::Blaster::Fire(const def::Transform& transform) {
    super::Fire(transform);
    auto param = ratchet::actor::bullet::Bullet::Param();
    param.transform = transform;
    param.transform.scale.x = _bullet_scale;
    param.transform.scale.y = _bullet_scale;
    param.transform.scale.z = _bullet_scale;

    if (super::_lock_on_position.has_value()) {
        Mof::CVector3 direction = super::_lock_on_position.value() - param.transform.position;
        direction.Normal(direction);
        param.speed = direction * _shot_speed;
        super::_lock_on_position.reset();
    } // if
    else {
        auto speed = Mof::CVector3(0.0f, 0.0f, -_shot_speed);
        speed.RotateAround(math::vec3::kZero, param.transform.rotate);
        param.speed = speed;
    } // else

    auto add = ratchet::factory::FactoryManager::Singleton().CreateActor<ratchet::actor::bullet::BlasterBullet>("../Resource/builder/blaster_bullet.json", &param);
    add->Start(param);
    Observable::Notify("AddRequest", add);
    return true;
}

void ratchet::actor::weapon::Blaster::Scaling(void) {
    this->_scaling = true;
}