#include "EnemyCollisionObject.h"

#include "../../Character/Enemy.h"


my::EnemyCollisionObject::EnemyCollisionObject() :
    super(),
    _owner() {
}

my::EnemyCollisionObject::~EnemyCollisionObject() {
}

void my::EnemyCollisionObject::SetOwner(std::any owner) {
    _owner = std::any_cast<std::shared_ptr<my::Enemy>>(owner);
}

std::any my::EnemyCollisionObject::GetOwner(void) const {
    return this->_owner;
}

const char* my::EnemyCollisionObject::GetType(void) const {
    return "EnemyCollisionObject";
}

std::optional<Mof::CSphere> my::EnemyCollisionObject::GetSphere(void) {
    if (auto owner = _owner.lock()) {
        if (owner->GetState() == my::ActorState::End) {
            return std::optional<Mof::CSphere>();
        } // if
        return Mof::CSphere(owner->GetPosition(), owner->GetVolume());
    } // if
    return std::optional<Mof::CSphere>();
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