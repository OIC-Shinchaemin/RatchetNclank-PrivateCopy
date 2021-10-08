#include "PyrocitorBulletCollisionComponent.h"

#include "../CollisionComponentDefine.h"


ratchet::component::collision::PyrocitorBulletCollisionComponent::PyrocitorBulletCollisionComponent(int priority) :
    super(priority) {
}

ratchet::component::collision::PyrocitorBulletCollisionComponent::PyrocitorBulletCollisionComponent(const PyrocitorBulletCollisionComponent& obj) :
    super(obj) {
}

ratchet::component::collision::PyrocitorBulletCollisionComponent::~PyrocitorBulletCollisionComponent() {
}

std::string ratchet::component::collision::PyrocitorBulletCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kPyrocitorBulletCollisionComponent;
 //   return "PyrocitorBulletCollisionComponent";
}

std::optional<Mof::CSphere> ratchet::component::collision::PyrocitorBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::PyrocitorBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::PyrocitorBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::PyrocitorBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::PyrocitorBulletCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::PyrocitorBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::PyrocitorBulletCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::PyrocitorBulletCollisionComponent>(*this);
}