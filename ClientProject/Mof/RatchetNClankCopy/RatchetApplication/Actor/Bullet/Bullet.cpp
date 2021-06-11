#include "Bullet.h"


void ratchet::actor::bullet::Bullet::BulletUpdate(float delta_time) {
    if (_exist_time.Tick(delta_time)) {
        super::End();
    } // if
}

ratchet::actor::bullet::Bullet::Bullet() :
    super(),
    _speed(),
    _exist_time() {
}

ratchet::actor::bullet::Bullet::~Bullet() {
}

bool ratchet::actor::bullet::Bullet::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

void ratchet::actor::bullet::Bullet::Start(const ratchet::actor::bullet::Bullet::Param& in) {
    super::Initialize((super::Param*)(&in));
    _speed = in.speed;
}