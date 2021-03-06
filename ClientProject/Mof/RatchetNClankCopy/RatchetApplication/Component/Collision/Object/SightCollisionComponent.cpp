#include "SightCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../SightRecognitionComponent.h"


ratchet::component::collision::SightCollisionComponent::SightCollisionComponent(int priority) :
    super(priority),
    _sight_recognition() {
}

ratchet::component::collision::SightCollisionComponent::SightCollisionComponent(const SightCollisionComponent& obj) :
    super(obj),
    _sight_recognition() {
}

ratchet::component::collision::SightCollisionComponent::~SightCollisionComponent() {
}

std::string ratchet::component::collision::SightCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kSightCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::SightCollisionComponent::GetSphere(void) {    
    if (_sight_recognition.expired()) {
        return std::optional<Mof::CSphere>();
    } // if
    if (super::GetOwner() ->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto sight = _sight_recognition.lock();
    return Mof::CSphere(super::GetOwner()->GetPosition(), sight->GetRange());
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::SightCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::SightCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::SightCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::SightCollisionComponent::GetSightObject(void) {
    if (_sight_recognition.expired()) {
        return std::optional<::ratchet::component::collision::SightObject>();
    } // if
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<::ratchet::component::collision::SightObject>();
    } // if
    return ::ratchet::component::collision::SightObject(super::GetOwner()->GetPosition(), super::GetOwner()->GetRotate());
}

bool ratchet::component::collision::SightCollisionComponent::Initialize(void) {
    super::Initialize();
    _sight_recognition = super::GetOwner()->GetComponent<ratchet::component::SightRecognitionComponent>();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::SightCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::SightCollisionComponent>(*this);
}