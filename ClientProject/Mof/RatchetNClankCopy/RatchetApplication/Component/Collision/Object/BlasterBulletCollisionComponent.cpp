#include "BlasterBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


ratchet::BlasterBulletCollisionComponent::BlasterBulletCollisionComponent(int priority) :
    super(priority) {
}

ratchet::BlasterBulletCollisionComponent::BlasterBulletCollisionComponent(const BlasterBulletCollisionComponent& obj) :
    super(obj) {
}

ratchet::BlasterBulletCollisionComponent::~BlasterBulletCollisionComponent() {
}

std::string ratchet::BlasterBulletCollisionComponent::GetType(void) const {
    return ratchet::CollisionComponentType::kBlasterBulletCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::BlasterBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> ratchet::BlasterBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::BlasterBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::BlasterBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<ratchet::SightObject> ratchet::BlasterBulletCollisionComponent::GetSightObject(void) {
    return std::optional<ratchet::SightObject>();
}

bool ratchet::BlasterBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::BlasterBulletCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::BlasterBulletCollisionComponent>(*this);
}

void ratchet::BlasterBulletCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}