#include "Action.h"

#include "Character/Enemy.h"


my::Action::Action() :
    _owner(),
    _active(false),
    _priority(0) {
}

my::Action::~Action() {
}

void my::Action::SetOwner(const std::shared_ptr<my::Enemy>& ptr) {
    this->_owner = ptr;
}

std::shared_ptr<my::Enemy> my::Action::GetOwner(void) const {
    if (!_owner.expired()) {
        return _owner.lock();
    } // if
    return nullptr;
}

bool my::Action::IsActive(void) const {
    return this->_active;
}

bool my::Action::Update(float delta_time) {
    // ŽÀs
    this->Execute(delta_time);
    // ”»’è
    if (this->InactiveCondition()) {
        this->_active = false;
    } // if
    return _active;
}

bool my::Action::Start(void) {
    if (_active) {
        return false;
    } // if
    _active = true;
    return _active;
}