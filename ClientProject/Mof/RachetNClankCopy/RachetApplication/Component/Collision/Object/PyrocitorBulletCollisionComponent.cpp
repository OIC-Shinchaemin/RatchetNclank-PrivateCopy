#include "PyrocitorBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


my::PyrocitorBulletCollisionComponent::PyrocitorBulletCollisionComponent(int priority) :
    super(priority) {
}

my::PyrocitorBulletCollisionComponent::PyrocitorBulletCollisionComponent(const PyrocitorBulletCollisionComponent& obj) :
    super(obj) {
}

my::PyrocitorBulletCollisionComponent::~PyrocitorBulletCollisionComponent() {
}

std::string my::PyrocitorBulletCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kPyrocitorBulletCollisionComponent;
 //   return "PyrocitorBulletCollisionComponent";
}

std::optional<Mof::CSphere> my::PyrocitorBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> my::PyrocitorBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::PyrocitorBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::PyrocitorBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::PyrocitorBulletCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::PyrocitorBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<my::Component> my::PyrocitorBulletCollisionComponent::Clone(void) {
    return std::make_shared<my::PyrocitorBulletCollisionComponent>(*this);
}