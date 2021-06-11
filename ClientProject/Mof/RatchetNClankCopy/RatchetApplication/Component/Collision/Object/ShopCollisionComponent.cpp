#include "ShopCollisionComponent.h"

#include "CollisionComponentDefine.h"


ratchet::ShopCollisionComponent::ShopCollisionComponent(int priority) :
    super(priority) ,
    _volume(5.0f){
}

ratchet::ShopCollisionComponent::ShopCollisionComponent(const ShopCollisionComponent& obj) :
    super(obj) ,
    _volume(obj._volume){
}

ratchet::ShopCollisionComponent::~ShopCollisionComponent() {
}

std::string ratchet::ShopCollisionComponent::GetType(void) const {
    return ratchet::CollisionComponentType::kShopCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::ShopCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> ratchet::ShopCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::ShopCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::ShopCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<ratchet::SightObject> ratchet::ShopCollisionComponent::GetSightObject(void) {
    return std::optional<ratchet::SightObject>();
}

bool ratchet::ShopCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::ShopCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::ShopCollisionComponent>(*this);
}

void ratchet::ShopCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}