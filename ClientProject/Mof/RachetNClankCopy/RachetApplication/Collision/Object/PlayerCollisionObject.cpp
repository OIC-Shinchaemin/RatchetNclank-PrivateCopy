#include "PlayerCollisionObject.h"

#include "../../Character/Player.h"


my::PlayerCollisionObject::PlayerCollisionObject() :
    super(),
    _owner(){
}

my::PlayerCollisionObject::~PlayerCollisionObject() {
}

void my::PlayerCollisionObject::SetOwner(std::any owner) {
    _owner = std::any_cast<std::shared_ptr<::Player>>(owner);
}

std::any my::PlayerCollisionObject::GetOwner(void) const {
    return this->_owner;
}

const char* my::PlayerCollisionObject::GetType(void) const {
    return "PlayerCollisionObject";
}

std::optional<Mof::CSphere> my::PlayerCollisionObject::GetSphere(void) {
    if (auto owner = _owner.lock()) {
        if (owner->GetState() == my::ActorState::End) {
            return std::optional<Mof::CSphere>();
        } // if

        return Mof::CSphere(owner->GetPosition(), owner->GetVolume());
    } // if
    return std::optional<Mof::CSphere>();
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