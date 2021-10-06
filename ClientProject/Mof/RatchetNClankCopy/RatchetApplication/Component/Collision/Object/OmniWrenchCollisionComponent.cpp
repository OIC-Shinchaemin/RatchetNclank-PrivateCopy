#include "OmniWrenchCollisionComponent.h"

#include "../CollisionComponentDefine.h"


ratchet::component::collision::OmniWrenchCollisionComponent::OmniWrenchCollisionComponent(int priority) :
    super(priority),
    _offset(0.8f){
}

ratchet::component::collision::OmniWrenchCollisionComponent::OmniWrenchCollisionComponent(const OmniWrenchCollisionComponent& obj) :
    super(obj) ,
    _offset(obj._offset){
}

ratchet::component::collision::OmniWrenchCollisionComponent::~OmniWrenchCollisionComponent() {
}

std::string ratchet::component::collision::OmniWrenchCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kOmniWrenchCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::OmniWrenchCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    Mof::CVector3 offset = math::vec3::kNegUnitZ * _offset;
    offset.RotateAround(math::vec3::kZero, super::GetOwner()->GetRotate());
    pos += offset;
    return Mof::CSphere(pos, 1.0f);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::OmniWrenchCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::OmniWrenchCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::OmniWrenchCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::OmniWrenchCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::OmniWrenchCollisionComponent::Initialize(void) {
    super::Initialize();
    super::Inactivate();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::OmniWrenchCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::OmniWrenchCollisionComponent>(*this);
}