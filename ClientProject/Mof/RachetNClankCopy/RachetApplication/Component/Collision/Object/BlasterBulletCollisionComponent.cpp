#include "BlasterBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


my::BlasterBulletCollisionComponent::BlasterBulletCollisionComponent(int priority) :
    super(priority) {
}

my::BlasterBulletCollisionComponent::BlasterBulletCollisionComponent(const BlasterBulletCollisionComponent& obj) :
    super(obj._priority) {
}

my::BlasterBulletCollisionComponent::~BlasterBulletCollisionComponent() {
}

std::string my::BlasterBulletCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kBlasterBulletCollisionComponent;
}

std::optional<Mof::CSphere> my::BlasterBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> my::BlasterBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::BlasterBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::BlasterBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::BlasterBulletCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::BlasterBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<my::Component> my::BlasterBulletCollisionComponent::Clone(void) {
    return std::make_shared<my::BlasterBulletCollisionComponent>(*this);
}

void my::BlasterBulletCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
    if (!this->GetSphere().has_value()) {
        return;
    } // if

    Mof::COLLISIONOUTGEOMETRY info;
    if (this->GetSphere().value().CollisionMesh(mesh, info)) {
        super::GetOwner()->End();
    } // if
}