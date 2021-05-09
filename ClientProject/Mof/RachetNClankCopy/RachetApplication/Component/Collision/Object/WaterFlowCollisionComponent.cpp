#include "WaterFlowCollisionComponent.h"

#include "CollisionComponentDefine.h"


my::WaterFlowCollisionComponent::WaterFlowCollisionComponent(int priority) :
    super(priority) {
}

my::WaterFlowCollisionComponent::WaterFlowCollisionComponent(const WaterFlowCollisionComponent& obj) :
    super(obj) {
}

my::WaterFlowCollisionComponent::~WaterFlowCollisionComponent() {
}

std::string my::WaterFlowCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kWaterFlowCollisionComponent;
}

std::optional<Mof::CSphere> my::WaterFlowCollisionComponent::GetSphere(void) {
    return std::optional<Mof::CSphere>();
}

std::optional<Mof::CBoxAABB> my::WaterFlowCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::WaterFlowCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::WaterFlowCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::PlaneObject> my::WaterFlowCollisionComponent::GetPlaneObject(void) {
    Mof::CMatrix44 scale, rotate, translate;
    scale.Scaling(super::GetOwner()->GetScale(), scale);
    rotate.RotationZXY(super::GetOwner()->GetRotate());
    translate.Translation(super::GetOwner()->GetPosition(), translate);
    Mof::CMatrix44 world = scale * rotate * translate;
    
    my::PlaneObject plane;
    plane.normal = math::vec3::kUnitY;
    plane.normal.TransformNormal(world);
    world.GetTranslation(plane.position);
    return plane;
}

std::optional<my::SightObject> my::WaterFlowCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::WaterFlowCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<my::Component> my::WaterFlowCollisionComponent::Clone(void) {
    return std::make_shared<my::WaterFlowCollisionComponent>(*this);
}