#include "ShopCollisionComponent.h"

#include "../CollisionComponentDefine.h"


ratchet::component::collision::ShopCollisionComponent::ShopCollisionComponent(int priority) :
    super(priority) ,
    _volume(5.0f){
}

ratchet::component::collision::ShopCollisionComponent::ShopCollisionComponent(const ShopCollisionComponent& obj) :
    super(obj) ,
    _volume(obj._volume){
}

ratchet::component::collision::ShopCollisionComponent::~ShopCollisionComponent() {
}

std::string ratchet::component::collision::ShopCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kShopCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::ShopCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::ShopCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::ShopCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::ShopCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::ShopCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::ShopCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::ShopCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::ShopCollisionComponent>(*this);
}

void ratchet::component::collision::ShopCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}