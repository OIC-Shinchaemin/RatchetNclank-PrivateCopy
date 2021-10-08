#include "QueenCollisionComponent.h"

#include "../CollisionComponentDefine.h"


ratchet::component::collision::QueenCollisionComponent::QueenCollisionComponent(int priority) :
    super(priority) ,
    _volume(5.0f){
}

ratchet::component::collision::QueenCollisionComponent::QueenCollisionComponent(const QueenCollisionComponent& obj) :
    super(obj) ,
    _volume(obj._volume){
}

ratchet::component::collision::QueenCollisionComponent::~QueenCollisionComponent() {
}

std::string ratchet::component::collision::QueenCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kQueenCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::QueenCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::QueenCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::QueenCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::QueenCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::QueenCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::QueenCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::QueenCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::QueenCollisionComponent>(*this);
}

void ratchet::component::collision::QueenCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}