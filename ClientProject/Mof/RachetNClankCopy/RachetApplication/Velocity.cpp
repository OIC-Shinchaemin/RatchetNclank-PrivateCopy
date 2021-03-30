#include "Velocity.h"


my::Velocity::Velocity() :
    _velocity(),
    _angular_velocity(),
    _velocity_force(),
    _angular_velocity_force(),
    _gravity(0.25f),
    _drag(0.8f),
    _angular_drag(0.8f) {
}

my::Velocity::~Velocity() {
}

void my::Velocity::SetVelocity(Mof::CVector3 value) {
    this->_velocity = value;
}

Mof::CVector3 my::Velocity::GetVelocity(void) const {
    return this->_velocity;
}

Mof::CVector3 my::Velocity::GetAngularVelocity(void) const {
    return this->_angular_velocity;
}

Mof::CVector3 my::Velocity::GetVelocityForce(void) const {
    return this->_velocity_force;
}

void my::Velocity::AddVelocityForce(Mof::CVector3 accele) {
    this->_velocity_force += accele;
}

void my::Velocity::AddAngularVelocityForce(Mof::CVector3 accele) {
    this->_angular_velocity_force += accele;
}

bool my::Velocity::Update(float delta_time) {
    _angular_velocity += _angular_velocity_force;
    _velocity += _velocity_force;

    _velocity.y -= _gravity;
    _velocity *= _drag;
    _angular_velocity *= _angular_drag;

    //_prev_velocity_force = _velocity_force;
    _velocity_force = Mof::CVector3();
    _angular_velocity_force = Mof::CVector3();
    return true;
}