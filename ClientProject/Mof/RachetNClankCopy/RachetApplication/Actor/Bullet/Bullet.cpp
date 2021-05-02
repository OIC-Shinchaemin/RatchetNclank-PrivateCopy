#include "Bullet.h"


void my::Bullet::BulletUpdate(float delta_time) {
    if (_exist_time.Tick(delta_time)) {
        super::End();
    } // if
}

my::Bullet::Bullet() :
    super(),
    _speed(),
    _exist_time() {
}

my::Bullet::~Bullet() {
}

bool my::Bullet::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

void my::Bullet::Start(const my::Bullet::Param& in) {
    super::Initialize((super::Param*)(&in));
    _speed = in.speed;
}