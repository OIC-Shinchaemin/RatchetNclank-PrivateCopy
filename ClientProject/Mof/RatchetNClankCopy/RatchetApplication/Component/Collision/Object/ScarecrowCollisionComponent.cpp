#include "ScarecrowCollisionComponent.h"

#include "../CollisionComponentDefine.h"


ratchet::component::collision::ScarecrowCollisionComponent::ScarecrowCollisionComponent(int priority) :
    super(priority) {
}

ratchet::component::collision::ScarecrowCollisionComponent::ScarecrowCollisionComponent(const ScarecrowCollisionComponent& obj) :
    super(obj) {
}

ratchet::component::collision::ScarecrowCollisionComponent::~ScarecrowCollisionComponent() {
}

std::string ratchet::component::collision::ScarecrowCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kScarecrowCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::ScarecrowCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 2.0f);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::ScarecrowCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::ScarecrowCollisionComponent::GetRay(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::ScarecrowCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::ScarecrowCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::ScarecrowCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::ScarecrowCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::ScarecrowCollisionComponent>(*this);
}

void ratchet::component::collision::ScarecrowCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}