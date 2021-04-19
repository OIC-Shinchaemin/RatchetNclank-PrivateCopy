#include "EnemySightCollisionObject.h"

#include "../../../Actor/Character/Enemy.h"


my::EnemySightCollisionObject::EnemySightCollisionObject() :
    super(),
    _owner(),
    _sight_recognition() {
}

my::EnemySightCollisionObject::~EnemySightCollisionObject() {
}

void my::EnemySightCollisionObject::SetOwner(std::any owner) {
    _owner = std::any_cast<std::shared_ptr<my::Enemy>>(owner);
}

std::any my::EnemySightCollisionObject::GetOwner(void) const {
    return this->_owner;
}

void my::EnemySightCollisionObject::SetSight(const std::shared_ptr<my::SightRecognition>& ptr) {
    this->_sight_recognition = ptr;
}

const char* my::EnemySightCollisionObject::GetType(void) const {
    return "EnemySightCollisionObject";
}

std::optional<Mof::CSphere> my::EnemySightCollisionObject::GetSphere(void) {    
    if (_owner.expired() || _sight_recognition.expired()) {
        return std::optional<Mof::CSphere>();
    } // if
    auto owner = _owner.lock();
    if (owner->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto sight = _sight_recognition.lock();
    return Mof::CSphere(owner->GetPosition(), sight->GetRange());
}

std::optional<Mof::CBoxAABB> my::EnemySightCollisionObject::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::EnemySightCollisionObject::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::EnemySightCollisionObject::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::EnemySightCollisionObject::GetSightObject(void) {
    if (_owner.expired() || _sight_recognition.expired()) {
        return std::optional<my::SightObject>();
    } // if
    auto owner = _owner.lock();
    if (owner->GetState() == my::ActorState::End) {
        return std::optional<my::SightObject>();
    } // if
    return my::SightObject(owner->GetPosition(), owner->GetRotate());
}