#include "Mechanical.h"

ratchet::actor::weapon::Mechanical::Mechanical() :
    super(),
    _shot_speed(0.0f),
    _interval(0.0f),
    _interval_max(0.0f),
    _bullet_count_max(0),
    _bullet_count(0),
    _lock_on_position(),
    _subject(){
}

ratchet::actor::weapon::Mechanical::~Mechanical() {
}

void ratchet::actor::weapon::Mechanical::SetLockOnPosition(Mof::CVector3 position) {
    this->_lock_on_position = position;
}

int ratchet::actor::weapon::Mechanical::GetBulletCount(void) const {
    return this->_bullet_count;
}

int ratchet::actor::weapon::Mechanical::GetBulletCountMax(void) const {
    return this->_bullet_count_max;
}

int ratchet::actor::weapon::Mechanical::GetBulletCountDecrased(void) const {
    return this->_bullet_count_max - this->GetBulletCount();
}

bool ratchet::actor::weapon::Mechanical::IsAction(void) const {
    return false;
}

bool ratchet::actor::weapon::Mechanical::Update(float delta_time) {
    _interval -= delta_time;
    super::Update(delta_time);
    return true;
}

bool ratchet::actor::weapon::Mechanical::Fire(const def::Transform& transform) {
    _bullet_count--;
    if (_bullet_count < 0) {
        _bullet_count = 0;
    } // if
    _interval = _interval_max;
    
    _subject.Notify(ratchet::actor::weapon::Mechanical::Info(this->_bullet_count, this->_bullet_count_max, this->GetName().c_str()));
    return true;
}

void ratchet::actor::weapon::Mechanical::ResetTargetPosition(void) {
    this->_lock_on_position.reset();
}

bool ratchet::actor::weapon::Mechanical::CanFire(void) const {
    return _bullet_count > 0 && _interval < 0.0f;
}

void ratchet::actor::weapon::Mechanical::AddBullet(std::uint32_t count) {
    _bullet_count += count;
    if (_bullet_count_max < _bullet_count) {
        _bullet_count = _bullet_count_max;
    } // if
}

void ratchet::actor::weapon::Mechanical::AddMechanicalInfoObserver(const std::shared_ptr<base::core::Observer<const ratchet::actor::weapon::Mechanical::Info&>>& ptr) {
    _subject.AddObserver(ptr);
}