#include "PyrocitorBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


ratchet::PyrocitorBulletCollisionComponent::PyrocitorBulletCollisionComponent(int priority) :
    super(priority) {
}

ratchet::PyrocitorBulletCollisionComponent::PyrocitorBulletCollisionComponent(const PyrocitorBulletCollisionComponent& obj) :
    super(obj) {
}

ratchet::PyrocitorBulletCollisionComponent::~PyrocitorBulletCollisionComponent() {
}

std::string ratchet::PyrocitorBulletCollisionComponent::GetType(void) const {
    return ratchet::CollisionComponentType::kPyrocitorBulletCollisionComponent;
 //   return "PyrocitorBulletCollisionComponent";
}

std::optional<Mof::CSphere> ratchet::PyrocitorBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> ratchet::PyrocitorBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::PyrocitorBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::PyrocitorBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<ratchet::SightObject> ratchet::PyrocitorBulletCollisionComponent::GetSightObject(void) {
    return std::optional<ratchet::SightObject>();
}

bool ratchet::PyrocitorBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PyrocitorBulletCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::PyrocitorBulletCollisionComponent>(*this);
}