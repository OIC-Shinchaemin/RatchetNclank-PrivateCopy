#include "Mechanical.h"

my::Mechanical::Mechanical() :
    super(),
    _shot_speed(0.0f),
    _interval(0.0f),
    _interval_max(0.0f),
    _bullet_count_max(0),
    _bullet_count(0),
    _lock_on_position(),
    _subject(){
}

my::Mechanical::~Mechanical() {
}

void my::Mechanical::SetLockOnPosition(Mof::CVector3 position) {
    this->_lock_on_position = position;
}

int my::Mechanical::GetBulletCount(void) const {
    return this->_bullet_count;
}

int my::Mechanical::GetBulletCountMax(void) const {
    return this->_bullet_count_max;
}

int my::Mechanical::GetBulletCountDecrased(void) const {
    return this->_bullet_count_max - this->GetBulletCount();
}

bool my::Mechanical::IsAction(void) const {
    return false;
}

bool my::Mechanical::Update(float delta_time) {
    _interval -= delta_time;
    super::Update(delta_time);
    return true;
}

bool my::Mechanical::Fire(const def::Transform& transform) {
    _bullet_count--;
    if (_bullet_count < 0) {
        _bullet_count = 0;
    } // if
    _interval = _interval_max;
    
    _subject.Notify(my::Mechanical::Info(this->_bullet_count, this->_bullet_count_max, this->GetName().c_str()));
    return true;
}

void my::Mechanical::ResetTargetPosition(void) {
    this->_lock_on_position.reset();
}

bool my::Mechanical::CanFire(void) const {
    return _bullet_count > 0 && _interval < 0.0f;
}

void my::Mechanical::AddBullet(std::uint32_t count) {
    _bullet_count += count;
    if (_bullet_count_max < _bullet_count) {
        _bullet_count = _bullet_count_max;
    } // if
}

void my::Mechanical::AddMechanicalInfoObserver(const std::shared_ptr<my::Observer<const my::Mechanical::Info&>>& ptr) {
    _subject.AddObserver(ptr);
}