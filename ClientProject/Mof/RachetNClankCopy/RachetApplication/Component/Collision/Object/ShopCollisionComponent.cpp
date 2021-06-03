#include "ShopCollisionComponent.h"

#include "CollisionComponentDefine.h"


my::ShopCollisionComponent::ShopCollisionComponent(int priority) :
    super(priority) ,
    _volume(5.0f){
}

my::ShopCollisionComponent::ShopCollisionComponent(const ShopCollisionComponent& obj) :
    super(obj) ,
    _volume(obj._volume){
}

my::ShopCollisionComponent::~ShopCollisionComponent() {
}

std::string my::ShopCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kShopCollisionComponent;
}

std::optional<Mof::CSphere> my::ShopCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, _volume);
}

std::optional<Mof::CBoxAABB> my::ShopCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::ShopCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::ShopCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::ShopCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::ShopCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<my::Component> my::ShopCollisionComponent::Clone(void) {
    return std::make_shared<my::ShopCollisionComponent>(*this);
}

void my::ShopCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}