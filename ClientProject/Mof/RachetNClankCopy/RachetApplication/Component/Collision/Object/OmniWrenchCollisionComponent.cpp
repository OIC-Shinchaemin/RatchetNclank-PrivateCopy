#include "OmniWrenchCollisionComponent.h"

#include "CollisionComponentDefine.h"


rachet::OmniWrenchCollisionComponent::OmniWrenchCollisionComponent(int priority) :
    super(priority),
    _offset(1.2f){
}

rachet::OmniWrenchCollisionComponent::OmniWrenchCollisionComponent(const OmniWrenchCollisionComponent& obj) :
    super(obj) ,
    _offset(obj._offset){
}

rachet::OmniWrenchCollisionComponent::~OmniWrenchCollisionComponent() {
}

std::string rachet::OmniWrenchCollisionComponent::GetType(void) const {
    return rachet::CollisionComponentType::kOmniWrenchCollisionComponent;
}

std::optional<Mof::CSphere> rachet::OmniWrenchCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == rachet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    Mof::CVector3 offset = math::vec3::kNegUnitZ * _offset;
    offset.RotateAround(math::vec3::kZero, super::GetOwner()->GetRotate());
    pos += offset;
    return Mof::CSphere(pos, 0.6f);
}

std::optional<Mof::CBoxAABB> rachet::OmniWrenchCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> rachet::OmniWrenchCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> rachet::OmniWrenchCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<rachet::SightObject> rachet::OmniWrenchCollisionComponent::GetSightObject(void) {
    return std::optional<rachet::SightObject>();
}

bool rachet::OmniWrenchCollisionComponent::Initialize(void) {
    super::Initialize();
    super::Inactivate();
    return true;
}

std::shared_ptr<rachet::Component> rachet::OmniWrenchCollisionComponent::Clone(void) {
    return std::make_shared<rachet::OmniWrenchCollisionComponent>(*this);
}