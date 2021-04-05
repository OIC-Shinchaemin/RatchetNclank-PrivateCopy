#include "Mechanical.h"

my::Mechanical::Mechanical() :
    super(),
    _shot_speed(0.0f),
    _interval(0.0f),
    _interval_max(0.0f),
    _bullet_count(0) {
}

my::Mechanical::~Mechanical() {
}

bool my::Mechanical::IsAction(void) const {
    return false;
}

bool my::Mechanical::Update(float delta_time) {
    super::Update(delta_time);
    _interval -= delta_time;
    return true;
}

bool my::Mechanical::Fire(const def::Transform& transform) {
    _bullet_count--;
    if (_bullet_count < 0) {
        _bullet_count = 0;
    } // if
    _interval = _interval_max;
    return true;
}

bool my::Mechanical::CanFire(void) const {
    return _bullet_count > 0 && _interval < 0.0f;
}