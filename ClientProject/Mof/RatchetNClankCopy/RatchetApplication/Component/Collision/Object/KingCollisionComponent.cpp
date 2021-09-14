#include "KingCollisionComponent.h"

#include "../CollisionComponentDefine.h"


ratchet::component::collision::KingCollisionComponent::KingCollisionComponent(int priority) :
    super(priority) ,
    _volume(5.0f){
}

ratchet::component::collision::KingCollisionComponent::KingCollisionComponent(const KingCollisionComponent& obj) :
    super(obj) ,
    _volume(obj._volume){
}

ratchet::component::collision::KingCollisionComponent::~KingCollisionComponent() {
}

std::string ratchet::component::collision::KingCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kKingCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::KingCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::KingCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::KingCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::KingCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::KingCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::KingCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::KingCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::KingCollisionComponent>(*this);
}

void ratchet::component::collision::KingCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}