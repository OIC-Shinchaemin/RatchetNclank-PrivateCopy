#include "Bullet.h"


void ratchet::Bullet::BulletUpdate(float delta_time) {
    if (_exist_time.Tick(delta_time)) {
        super::End();
    } // if
}

ratchet::Bullet::Bullet() :
    super(),
    _speed(),
    _exist_time() {
}

ratchet::Bullet::~Bullet() {
}

bool ratchet::Bullet::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

void ratchet::Bullet::Start(const ratchet::Bullet::Param& in) {
    super::Initialize((super::Param*)(&in));
    _speed = in.speed;
}