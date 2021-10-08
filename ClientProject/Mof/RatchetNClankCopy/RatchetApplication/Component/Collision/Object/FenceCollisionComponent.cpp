#include "FenceCollisionComponent.h"

#include "../CollisionComponentDefine.h"


ratchet::component::collision::FenceCollisionComponent::FenceCollisionComponent(int priority) :
    super(priority),
    _height(3.0f) {
}

ratchet::component::collision::FenceCollisionComponent::FenceCollisionComponent(const FenceCollisionComponent& obj) :
    super(obj),
    _height(obj._height) {
}

ratchet::component::collision::FenceCollisionComponent::~FenceCollisionComponent() {
}

std::string ratchet::component::collision::FenceCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kFenceCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::FenceCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    float volume = 1.2f;
    pos.y += volume * 0.5f;
    return Mof::CSphere(pos, volume);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::FenceCollisionComponent::GetBox(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CBoxAABB>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    auto rot = super::GetOwner()->GetRotate();
    float volume = 2.5f;
    auto size = Mof::CVector3(volume, volume * 2.0f, volume);
    float offset_z = 1.5f;
    pos.z += offset_z;
    //size.RotationY(rot.y);
    return Mof::CBoxAABB(pos, size);
}

std::optional<Mof::CRay3D> ratchet::component::collision::FenceCollisionComponent::GetRay(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CRay3D>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CRay3D(pos, math::vec3::kNegUnitY);
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::FenceCollisionComponent::GetMesh(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::LPMeshContainer>();
    } // if
    return _mesh.lock()->GetMeshContainer().get();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::FenceCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::FenceCollisionComponent::Initialize(void) {
    super::Initialize();
    _mesh = super::GetOwner()->GetComponent<ratchet::component::MeshComponent>();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::FenceCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::FenceCollisionComponent>(*this);
}

void ratchet::component::collision::FenceCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}