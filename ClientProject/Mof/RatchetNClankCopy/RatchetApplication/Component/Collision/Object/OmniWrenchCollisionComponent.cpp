#include "OmniWrenchCollisionComponent.h"

#include "CollisionComponentDefine.h"


ratchet::OmniWrenchCollisionComponent::OmniWrenchCollisionComponent(int priority) :
    super(priority),
    _offset(1.2f){
}

ratchet::OmniWrenchCollisionComponent::OmniWrenchCollisionComponent(const OmniWrenchCollisionComponent& obj) :
    super(obj) ,
    _offset(obj._offset){
}

ratchet::OmniWrenchCollisionComponent::~OmniWrenchCollisionComponent() {
}

std::string ratchet::OmniWrenchCollisionComponent::GetType(void) const {
    return ratchet::CollisionComponentType::kOmniWrenchCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::OmniWrenchCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    Mof::CVector3 offset = math::vec3::kNegUnitZ * _offset;
    offset.RotateAround(math::vec3::kZero, super::GetOwner()->GetRotate());
    pos += offset;
    return Mof::CSphere(pos, 0.6f);
}

std::optional<Mof::CBoxAABB> ratchet::OmniWrenchCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::OmniWrenchCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::OmniWrenchCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<ratchet::SightObject> ratchet::OmniWrenchCollisionComponent::GetSightObject(void) {
    return std::optional<ratchet::SightObject>();
}

bool ratchet::OmniWrenchCollisionComponent::Initialize(void) {
    super::Initialize();
    super::Inactivate();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::OmniWrenchCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::OmniWrenchCollisionComponent>(*this);
}