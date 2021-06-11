#include "BlasterBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


rachet::BlasterBulletCollisionComponent::BlasterBulletCollisionComponent(int priority) :
    super(priority) {
}

rachet::BlasterBulletCollisionComponent::BlasterBulletCollisionComponent(const BlasterBulletCollisionComponent& obj) :
    super(obj) {
}

rachet::BlasterBulletCollisionComponent::~BlasterBulletCollisionComponent() {
}

std::string rachet::BlasterBulletCollisionComponent::GetType(void) const {
    return rachet::CollisionComponentType::kBlasterBulletCollisionComponent;
}

std::optional<Mof::CSphere> rachet::BlasterBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == rachet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> rachet::BlasterBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> rachet::BlasterBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> rachet::BlasterBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<rachet::SightObject> rachet::BlasterBulletCollisionComponent::GetSightObject(void) {
    return std::optional<rachet::SightObject>();
}

bool rachet::BlasterBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<rachet::Component> rachet::BlasterBulletCollisionComponent::Clone(void) {
    return std::make_shared<rachet::BlasterBulletCollisionComponent>(*this);
}

void rachet::BlasterBulletCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}