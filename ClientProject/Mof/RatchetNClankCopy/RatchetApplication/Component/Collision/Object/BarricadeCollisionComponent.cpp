#include "BarricadeCollisionComponent.h"

#include "../CollisionComponentDefine.h"


ratchet::component::collision::BarricadeCollisionComponent::BarricadeCollisionComponent(int priority) :
    super(priority) {
}

ratchet::component::collision::BarricadeCollisionComponent::BarricadeCollisionComponent(const BarricadeCollisionComponent& obj) :
    super(obj) {
}

ratchet::component::collision::BarricadeCollisionComponent::~BarricadeCollisionComponent() {
}

std::string ratchet::component::collision::BarricadeCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBarricadeCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::BarricadeCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    float volume = 1.2f;
    pos.y += volume * 0.5f;
    return Mof::CSphere(pos, volume);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::BarricadeCollisionComponent::GetBox(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CBoxAABB>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    float volume = 1.0f;
    auto size = Mof::CVector3(volume, volume * 2.0f, volume);
    return Mof::CBoxAABB(pos, size);
}

std::optional<Mof::CRay3D> ratchet::component::collision::BarricadeCollisionComponent::GetRay(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CRay3D(pos, math::vec3::kNegUnitY);
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::BarricadeCollisionComponent::GetMesh(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::LPMeshContainer>();
    } // if
    return _mesh.lock()->GetMeshContainer().get();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::BarricadeCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::BarricadeCollisionComponent::Initialize(void) {
    super::Initialize();
    _mesh = super::GetOwner()->GetComponent<ratchet::component::MeshComponent>();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::BarricadeCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::BarricadeCollisionComponent>(*this);
}

void ratchet::component::collision::BarricadeCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}