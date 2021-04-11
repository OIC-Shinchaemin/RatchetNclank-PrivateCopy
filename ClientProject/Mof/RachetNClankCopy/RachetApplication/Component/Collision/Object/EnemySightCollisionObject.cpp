#include "EnemySightCollisionObject.h"

#include "../../SightRecognitionComponent.h"


my::EnemySightCollisionObject::EnemySightCollisionObject(int priority) :
    super(priority),
    _sight_recognition() {
}

my::EnemySightCollisionObject::EnemySightCollisionObject(const EnemySightCollisionObject& obj) :
    super(obj._priority),
    _sight_recognition() {
}

my::EnemySightCollisionObject::~EnemySightCollisionObject() {
}

void my::EnemySightCollisionObject::SetSight(const std::shared_ptr<my::SightRecognitionComponent>& ptr) {
    this->_sight_recognition = ptr;
}

std::string my::EnemySightCollisionObject::GetType(void) const {
    return "EnemySightCollisionObject";
}

std::optional<Mof::CSphere> my::EnemySightCollisionObject::GetSphere(void) {    
    if (_sight_recognition.expired()) {
        return std::optional<Mof::CSphere>();
    } // if
    if (super::GetOwner() ->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto sight = _sight_recognition.lock();
    return Mof::CSphere(super::GetOwner()->GetPosition(), sight->GetRange());
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
    if (_sight_recognition.expired()) {
        return std::optional<my::SightObject>();
    } // if
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<my::SightObject>();
    } // if
    return my::SightObject(super::GetOwner()->GetPosition(), super::GetOwner()->GetRotate());
}

std::shared_ptr<my::Component> my::EnemySightCollisionObject::Clone(void) {
    return std::make_shared<my::EnemySightCollisionObject>(*this);
}