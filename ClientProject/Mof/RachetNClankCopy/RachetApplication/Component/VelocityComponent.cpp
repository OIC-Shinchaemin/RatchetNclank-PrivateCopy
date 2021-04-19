#include "VelocityComponent.h"


my::VelocityComponent::VelocityComponent(int priority) :
    super(priority),
    _velocity(),
    _angular_velocity(),
    _velocity_force(),
    _angular_velocity_force(),
    _gravity(0.25f),
    _drag(0.8f),
    _angular_drag(0.8f),
    _use_gravity(true) {
}

my::VelocityComponent::VelocityComponent(const VelocityComponent& obj) :
    super(obj._priority),
    _velocity(obj._velocity),
    _angular_velocity(obj._angular_velocity),
    _velocity_force(obj._velocity_force),
    _angular_velocity_force(obj._angular_velocity_force),
    _gravity(obj._gravity),
    _drag(obj._drag),
    _angular_drag(obj._angular_drag),
    _use_gravity(obj._use_gravity) {
}

my::VelocityComponent::~VelocityComponent() {
}

void my::VelocityComponent::SetVelocity(Mof::CVector3 value) {
    this->_velocity = value;
}

void my::VelocityComponent::SetGravity(float value) {
    this->_gravity = value;
}

void my::VelocityComponent::SetDrag(float value) {
    this->_drag = value;
}

void my::VelocityComponent::SetUseGravity(bool use) {
    this->_use_gravity = use;
}

std::string my::VelocityComponent::GetType(void) const {
    return "VelocityComponent";
}

Mof::CVector3 my::VelocityComponent::GetVelocity(void) const {
    return this->_velocity;
}

Mof::CVector3 my::VelocityComponent::GetAngularVelocity(void) const {
    return this->_angular_velocity;
}

Mof::CVector3 my::VelocityComponent::GetVelocityForce(void) const {
    return this->_velocity_force;
}

void my::VelocityComponent::AddVelocityForce(Mof::CVector3 accele) {
    this->_velocity_force += accele;
}

void my::VelocityComponent::AddAngularVelocityForce(Mof::CVector3 accele) {
    this->_angular_velocity_force += accele;
}

bool my::VelocityComponent::Initialize(void) {
    super::Initialize();
    super::Start();
    return true;
}

bool my::VelocityComponent::Update(float delta_time) {
    _angular_velocity += _angular_velocity_force;
    _velocity += _velocity_force;

    if (_use_gravity) {
        _velocity.y -= _gravity;
    } // if
    _velocity *= _drag;
    _angular_velocity *= _angular_drag;

    //_prev_velocity_force = _velocity_force;
    _velocity_force = Mof::CVector3();
    _angular_velocity_force = Mof::CVector3();
    return true;
}

bool my::VelocityComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::VelocityComponent::Clone(void) {
    return std::make_shared<my::VelocityComponent>(*this);
}