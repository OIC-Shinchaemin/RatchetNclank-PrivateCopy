#include "PyrocitorBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


rachet::PyrocitorBulletCollisionComponent::PyrocitorBulletCollisionComponent(int priority) :
    super(priority) {
}

rachet::PyrocitorBulletCollisionComponent::PyrocitorBulletCollisionComponent(const PyrocitorBulletCollisionComponent& obj) :
    super(obj) {
}

rachet::PyrocitorBulletCollisionComponent::~PyrocitorBulletCollisionComponent() {
}

std::string rachet::PyrocitorBulletCollisionComponent::GetType(void) const {
    return rachet::CollisionComponentType::kPyrocitorBulletCollisionComponent;
 //   return "PyrocitorBulletCollisionComponent";
}

std::optional<Mof::CSphere> rachet::PyrocitorBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == rachet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> rachet::PyrocitorBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> rachet::PyrocitorBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> rachet::PyrocitorBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<rachet::SightObject> rachet::PyrocitorBulletCollisionComponent::GetSightObject(void) {
    return std::optional<rachet::SightObject>();
}

bool rachet::PyrocitorBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<rachet::Component> rachet::PyrocitorBulletCollisionComponent::Clone(void) {
    return std::make_shared<rachet::PyrocitorBulletCollisionComponent>(*this);
}