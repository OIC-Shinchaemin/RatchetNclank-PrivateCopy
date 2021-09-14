#include "WaterFlowCollisionComponent.h"

#include "../CollisionComponentDefine.h"


ratchet::component::collision::WaterFlowCollisionComponent::WaterFlowCollisionComponent(int priority) :
    super(priority) {
}

ratchet::component::collision::WaterFlowCollisionComponent::WaterFlowCollisionComponent(const WaterFlowCollisionComponent& obj) :
    super(obj) {
}

ratchet::component::collision::WaterFlowCollisionComponent::~WaterFlowCollisionComponent() {
}

std::string ratchet::component::collision::WaterFlowCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kWaterFlowCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::WaterFlowCollisionComponent::GetSphere(void) {
    return std::optional<Mof::CSphere>();
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::WaterFlowCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::WaterFlowCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::WaterFlowCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<ratchet::component::collision::PlaneObject> ratchet::component::collision::WaterFlowCollisionComponent::GetPlaneObject(void) {
    Mof::CMatrix44 scale, rotate, translate;
    scale.Scaling(super::GetOwner()->GetScale(), scale);
    rotate.RotationZXY(super::GetOwner()->GetRotate());
    translate.Translation(super::GetOwner()->GetPosition(), translate);
    Mof::CMatrix44 world = scale * rotate * translate;
    
    ratchet::component::collision::PlaneObject plane;
    plane.normal = math::vec3::kUnitY;
    plane.normal.TransformNormal(world);
    world.GetTranslation(plane.position);
    return plane;
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::WaterFlowCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::WaterFlowCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::WaterFlowCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::WaterFlowCollisionComponent>(*this);
}