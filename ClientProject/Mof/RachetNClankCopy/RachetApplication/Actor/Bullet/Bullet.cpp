#include "Bullet.h"


void rachet::Bullet::BulletUpdate(float delta_time) {
    if (_exist_time.Tick(delta_time)) {
        super::End();
    } // if
}

rachet::Bullet::Bullet() :
    super(),
    _speed(),
    _exist_time() {
}

rachet::Bullet::~Bullet() {
}

bool rachet::Bullet::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

void rachet::Bullet::Start(const rachet::Bullet::Param& in) {
    super::Initialize((super::Param*)(&in));
    _speed = in.speed;
}