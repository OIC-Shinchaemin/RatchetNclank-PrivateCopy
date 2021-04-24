#include "ShipCollisionComponent.h"

#include "CollisionComponentDefine.h"


my::ShipCollisionComponent::ShipCollisionComponent(int priority) :
    super(priority) {
}

my::ShipCollisionComponent::ShipCollisionComponent(const ShipCollisionComponent& obj) :
    super(obj._priority) {
}

my::ShipCollisionComponent::~ShipCollisionComponent() {
}

std::string my::ShipCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kShipCollisionComponent;
}

std::optional<Mof::CSphere> my::ShipCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> my::ShipCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::ShipCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::ShipCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::ShipCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::ShipCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<my::Component> my::ShipCollisionComponent::Clone(void) {
    return std::make_shared<my::ShipCollisionComponent>(*this);
}

void my::ShipCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh) {
    if (!this->GetSphere().has_value()) {
        return;
    } // if

    Mof::COLLISIONOUTGEOMETRY info;
    if (this->GetSphere().value().CollisionMesh(mesh, info)) {
        super::GetOwner()->End();
    } // if
}