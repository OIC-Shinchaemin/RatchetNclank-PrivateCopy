#include "VelocityComponent.h"


ratchet::component::VelocityComponent::VelocityComponent(int priority) :
    super(priority),
    _velocity(),
    _angular_velocity(),
    _velocity_force(),
    _angular_velocity_force(),
    _gravity(0.25f),
    _drag(0.8f),
    _angular_drag(0.8f),
    _use_gravity(true),
    _sleep(false) {
}

ratchet::component::VelocityComponent::VelocityComponent(const VelocityComponent& obj) :
    super(obj),
    _velocity(obj._velocity),
    _angular_velocity(obj._angular_velocity),
    _velocity_force(obj._velocity_force),
    _angular_velocity_force(obj._angular_velocity_force),
    _gravity(obj._gravity),
    _drag(obj._drag),
    _angular_drag(obj._angular_drag),
    _use_gravity(obj._use_gravity),
    _sleep(obj._sleep) {
}

ratchet::component::VelocityComponent::~VelocityComponent() {
}

void ratchet::component::VelocityComponent::SetVelocity(Mof::CVector3 value) {
    this->_velocity = value;
}

void ratchet::component::VelocityComponent::SetGravity(float value) {
    this->_gravity = value;
}

void ratchet::component::VelocityComponent::SetDrag(float value) {
    this->_drag = value;
}

void ratchet::component::VelocityComponent::SetUseGravity(bool use) {
    this->_use_gravity = use;
}

void ratchet::component::VelocityComponent::SetSleep(bool b) {
    this->_sleep = b;
}

std::string ratchet::component::VelocityComponent::GetType(void) const {
    return "VelocityComponent";
}

Mof::CVector3 ratchet::component::VelocityComponent::GetVelocity(void) const {
    return this->_velocity;
}

Mof::CVector3 ratchet::component::VelocityComponent::GetAngularVelocity(void) const {
    return this->_angular_velocity;
}

Mof::CVector3 ratchet::component::VelocityComponent::GetVelocityForce(void) const {
    return this->_velocity_force;
}

float ratchet::component::VelocityComponent::GetDrag(void) const {
    return this->_drag;
}

float ratchet::component::VelocityComponent::GetGravity(void) const {
    return this->_gravity;
}

bool ratchet::component::VelocityComponent::IsSleep(void) const {
    return this->_sleep;
}

void ratchet::component::VelocityComponent::AddVelocityForce(Mof::CVector3 accele) {
    this->_velocity_force += accele;
}

void ratchet::component::VelocityComponent::AddAngularVelocityForce(Mof::CVector3 accele) {
    this->_angular_velocity_force += accele;
}

bool ratchet::component::VelocityComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    return true;
}

bool ratchet::component::VelocityComponent::Update(float delta_time) {
    _angular_velocity += _angular_velocity_force;
    _velocity += _velocity_force;

    if (_use_gravity) {
        _velocity.y -= _gravity;
    } // if
    
    _velocity *= _drag;
    _angular_velocity *= _angular_drag;
    _velocity_force = Mof::CVector3();
    _angular_velocity_force = Mof::CVector3();
    return true;
}

bool ratchet::component::VelocityComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::VelocityComponent::Clone(void) {
    return std::make_shared<ratchet::component::VelocityComponent>(*this);
}