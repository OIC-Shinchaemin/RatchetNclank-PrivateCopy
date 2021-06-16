#include "BlasterBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


ratchet::component::collision::BlasterBulletCollisionComponent::BlasterBulletCollisionComponent(int priority) :
    super(priority) {
}

ratchet::component::collision::BlasterBulletCollisionComponent::BlasterBulletCollisionComponent(const BlasterBulletCollisionComponent& obj) :
    super(obj) {
}

ratchet::component::collision::BlasterBulletCollisionComponent::~BlasterBulletCollisionComponent() {
}

std::string ratchet::component::collision::BlasterBulletCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBlasterBulletCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::BlasterBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::BlasterBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::BlasterBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::BlasterBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::BlasterBulletCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::BlasterBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::BlasterBulletCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::BlasterBulletCollisionComponent>(*this);
}

void ratchet::component::collision::BlasterBulletCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}