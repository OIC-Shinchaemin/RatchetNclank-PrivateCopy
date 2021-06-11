#include "ShopCollisionComponent.h"

#include "CollisionComponentDefine.h"


rachet::ShopCollisionComponent::ShopCollisionComponent(int priority) :
    super(priority) ,
    _volume(5.0f){
}

rachet::ShopCollisionComponent::ShopCollisionComponent(const ShopCollisionComponent& obj) :
    super(obj) ,
    _volume(obj._volume){
}

rachet::ShopCollisionComponent::~ShopCollisionComponent() {
}

std::string rachet::ShopCollisionComponent::GetType(void) const {
    return rachet::CollisionComponentType::kShopCollisionComponent;
}

std::optional<Mof::CSphere> rachet::ShopCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == rachet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> rachet::ShopCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> rachet::ShopCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> rachet::ShopCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<rachet::SightObject> rachet::ShopCollisionComponent::GetSightObject(void) {
    return std::optional<rachet::SightObject>();
}

bool rachet::ShopCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<rachet::Component> rachet::ShopCollisionComponent::Clone(void) {
    return std::make_shared<rachet::ShopCollisionComponent>(*this);
}

void rachet::ShopCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}