#include "EnemyCollisionObject.h"

#include "../../../Actor/Character/Enemy.h"


my::EnemyCollisionObject::EnemyCollisionObject(int priority) :
    super(priority) {
}

my::EnemyCollisionObject::EnemyCollisionObject(const EnemyCollisionObject& obj) :
    super(obj._priority) {
}

my::EnemyCollisionObject::~EnemyCollisionObject() {
}

std::string my::EnemyCollisionObject::GetType(void) const {
    return "EnemyCollisionObject";
}

std::optional<Mof::CSphere> my::EnemyCollisionObject::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto owner = std::dynamic_pointer_cast<my::Enemy>(super::GetOwner());
    return Mof::CSphere(super::GetOwner()->GetPosition(), owner->GetVolume());
}

std::optional<Mof::CBoxAABB> my::EnemyCollisionObject::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::EnemyCollisionObject::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::EnemyCollisionObject::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::EnemyCollisionObject::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

std::shared_ptr<my::Component> my::EnemyCollisionObject::Clone(void) {
    return std::make_shared<my::EnemyCollisionObject>(*this);
}
