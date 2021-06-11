#include "Mechanical.h"

ratchet::Mechanical::Mechanical() :
    super(),
    _shot_speed(0.0f),
    _interval(0.0f),
    _interval_max(0.0f),
    _bullet_count_max(0),
    _bullet_count(0),
    _lock_on_position(),
    _subject(){
}

ratchet::Mechanical::~Mechanical() {
}

void ratchet::Mechanical::SetLockOnPosition(Mof::CVector3 position) {
    this->_lock_on_position = position;
}

int ratchet::Mechanical::GetBulletCount(void) const {
    return this->_bullet_count;
}

int ratchet::Mechanical::GetBulletCountMax(void) const {
    return this->_bullet_count_max;
}

int ratchet::Mechanical::GetBulletCountDecrased(void) const {
    return this->_bullet_count_max - this->GetBulletCount();
}

bool ratchet::Mechanical::IsAction(void) const {
    return false;
}

bool ratchet::Mechanical::Update(float delta_time) {
    _interval -= delta_time;
    super::Update(delta_time);
    return true;
}

bool ratchet::Mechanical::Fire(const def::Transform& transform) {
    _bullet_count--;
    if (_bullet_count < 0) {
        _bullet_count = 0;
    } // if
    _interval = _interval_max;
    
    _subject.Notify(ratchet::Mechanical::Info(this->_bullet_count, this->_bullet_count_max, this->GetName().c_str()));
    return true;
}

void ratchet::Mechanical::ResetTargetPosition(void) {
    this->_lock_on_position.reset();
}

bool ratchet::Mechanical::CanFire(void) const {
    return _bullet_count > 0 && _interval < 0.0f;
}

void ratchet::Mechanical::AddBullet(std::uint32_t count) {
    _bullet_count += count;
    if (_bullet_count_max < _bullet_count) {
        _bullet_count = _bullet_count_max;
    } // if
}

void ratchet::Mechanical::AddMechanicalInfoObserver(const std::shared_ptr<base::core::Observer<const ratchet::Mechanical::Info&>>& ptr) {
    _subject.AddObserver(ptr);
}