#include "PlayerCollisionObject.h"

#include "../../../Actor/Character/Player.h"


my::PlayerCollisionObject::PlayerCollisionObject(int priority) :
    super(priority) {
}

my::PlayerCollisionObject::PlayerCollisionObject(const PlayerCollisionObject& obj) :
    super(obj._priority) {
}

my::PlayerCollisionObject::~PlayerCollisionObject() {
}

std::string my::PlayerCollisionObject::GetType(void) const {
    return "PlayerCollisionObject";
}

std::optional<Mof::CSphere> my::PlayerCollisionObject::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto owner = std::dynamic_pointer_cast<Player>(super::GetOwner());
    return Mof::CSphere(super::GetOwner()->GetPosition(), owner->GetVolume());
}

std::optional<Mof::CBoxAABB> my::PlayerCollisionObject::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::PlayerCollisionObject::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::PlayerCollisionObject::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::PlayerCollisionObject::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

std::shared_ptr<my::Component> my::PlayerCollisionObject::Clone(void) {
    return std::make_shared<my::PlayerCollisionObject>(*this);
}
