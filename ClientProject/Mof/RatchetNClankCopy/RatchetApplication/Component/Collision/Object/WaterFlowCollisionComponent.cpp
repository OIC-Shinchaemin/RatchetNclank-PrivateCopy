#include "WaterFlowCollisionComponent.h"

#include "CollisionComponentDefine.h"


ratchet::WaterFlowCollisionComponent::WaterFlowCollisionComponent(int priority) :
    super(priority) {
}

ratchet::WaterFlowCollisionComponent::WaterFlowCollisionComponent(const WaterFlowCollisionComponent& obj) :
    super(obj) {
}

ratchet::WaterFlowCollisionComponent::~WaterFlowCollisionComponent() {
}

std::string ratchet::WaterFlowCollisionComponent::GetType(void) const {
    return ratchet::CollisionComponentType::kWaterFlowCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::WaterFlowCollisionComponent::GetSphere(void) {
    return std::optional<Mof::CSphere>();
}

std::optional<Mof::CBoxAABB> ratchet::WaterFlowCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::WaterFlowCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::WaterFlowCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<ratchet::PlaneObject> ratchet::WaterFlowCollisionComponent::GetPlaneObject(void) {
    Mof::CMatrix44 scale, rotate, translate;
    scale.Scaling(super::GetOwner()->GetScale(), scale);
    rotate.RotationZXY(super::GetOwner()->GetRotate());
    translate.Translation(super::GetOwner()->GetPosition(), translate);
    Mof::CMatrix44 world = scale * rotate * translate;
    
    ratchet::PlaneObject plane;
    plane.normal = math::vec3::kUnitY;
    plane.normal.TransformNormal(world);
    world.GetTranslation(plane.position);
    return plane;
}

std::optional<ratchet::SightObject> ratchet::WaterFlowCollisionComponent::GetSightObject(void) {
    return std::optional<ratchet::SightObject>();
}

bool ratchet::WaterFlowCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::WaterFlowCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::WaterFlowCollisionComponent>(*this);
}