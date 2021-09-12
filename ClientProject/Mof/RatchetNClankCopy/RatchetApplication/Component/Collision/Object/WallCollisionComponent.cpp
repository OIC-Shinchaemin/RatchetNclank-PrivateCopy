#include "WallCollisionComponent.h"

#include "CollisionComponentDefine.h"


ratchet::component::collision::WallCollisionComponent::WallCollisionComponent(int priority) :
    super(priority) ,
    _volume(23.0f){
}

ratchet::component::collision::WallCollisionComponent::WallCollisionComponent(const WallCollisionComponent& obj) :
    super(obj) ,
    _volume(obj._volume){
}

ratchet::component::collision::WallCollisionComponent::~WallCollisionComponent() {
}

std::string ratchet::component::collision::WallCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kWallCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::WallCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::WallCollisionComponent::GetBox(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CBoxAABB>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    auto size = Mof::CVector3(_volume, _volume, _volume);
    return Mof::CBoxAABB(pos, size);
}

std::optional<Mof::CRay3D> ratchet::component::collision::WallCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::WallCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::WallCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::WallCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::WallCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::WallCollisionComponent>(*this);
}

void ratchet::component::collision::WallCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}