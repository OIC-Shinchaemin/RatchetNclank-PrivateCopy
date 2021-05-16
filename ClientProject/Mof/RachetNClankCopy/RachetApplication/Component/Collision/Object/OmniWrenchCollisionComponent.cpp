#include "OmniWrenchCollisionComponent.h"

#include "CollisionComponentDefine.h"


my::OmniWrenchCollisionComponent::OmniWrenchCollisionComponent(int priority) :
    super(priority),
    _offset(1.2f){
}

my::OmniWrenchCollisionComponent::OmniWrenchCollisionComponent(const OmniWrenchCollisionComponent& obj) :
    super(obj) ,
    _offset(obj._offset){
}

my::OmniWrenchCollisionComponent::~OmniWrenchCollisionComponent() {
}

std::string my::OmniWrenchCollisionComponent::GetType(void) const {
    return my::CollisionComponentType::kOmniWrenchCollisionComponent;
}

std::optional<Mof::CSphere> my::OmniWrenchCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    Mof::CVector3 offset = math::vec3::kNegUnitZ * _offset;
    offset.RotateAround(math::vec3::kZero, super::GetOwner()->GetRotate());
    pos += offset;
    return Mof::CSphere(pos, 0.6f);
}

std::optional<Mof::CBoxAABB> my::OmniWrenchCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::OmniWrenchCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::OmniWrenchCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::OmniWrenchCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::OmniWrenchCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<my::Component> my::OmniWrenchCollisionComponent::Clone(void) {
    return std::make_shared<my::OmniWrenchCollisionComponent>(*this);
}