#include "WaterFlowCollisionComponent.h"

#include "CollisionComponentDefine.h"


rachet::WaterFlowCollisionComponent::WaterFlowCollisionComponent(int priority) :
    super(priority) {
}

rachet::WaterFlowCollisionComponent::WaterFlowCollisionComponent(const WaterFlowCollisionComponent& obj) :
    super(obj) {
}

rachet::WaterFlowCollisionComponent::~WaterFlowCollisionComponent() {
}

std::string rachet::WaterFlowCollisionComponent::GetType(void) const {
    return rachet::CollisionComponentType::kWaterFlowCollisionComponent;
}

std::optional<Mof::CSphere> rachet::WaterFlowCollisionComponent::GetSphere(void) {
    return std::optional<Mof::CSphere>();
}

std::optional<Mof::CBoxAABB> rachet::WaterFlowCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> rachet::WaterFlowCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> rachet::WaterFlowCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<rachet::PlaneObject> rachet::WaterFlowCollisionComponent::GetPlaneObject(void) {
    Mof::CMatrix44 scale, rotate, translate;
    scale.Scaling(super::GetOwner()->GetScale(), scale);
    rotate.RotationZXY(super::GetOwner()->GetRotate());
    translate.Translation(super::GetOwner()->GetPosition(), translate);
    Mof::CMatrix44 world = scale * rotate * translate;
    
    rachet::PlaneObject plane;
    plane.normal = math::vec3::kUnitY;
    plane.normal.TransformNormal(world);
    world.GetTranslation(plane.position);
    return plane;
}

std::optional<rachet::SightObject> rachet::WaterFlowCollisionComponent::GetSightObject(void) {
    return std::optional<rachet::SightObject>();
}

bool rachet::WaterFlowCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<rachet::Component> rachet::WaterFlowCollisionComponent::Clone(void) {
    return std::make_shared<rachet::WaterFlowCollisionComponent>(*this);
}