#include "SightCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../SightRecognitionComponent.h"


ratchet::SightCollisionComponent::SightCollisionComponent(int priority) :
    super(priority),
    _sight_recognition() {
}

ratchet::SightCollisionComponent::SightCollisionComponent(const SightCollisionComponent& obj) :
    super(obj),
    _sight_recognition() {
}

ratchet::SightCollisionComponent::~SightCollisionComponent() {
}

std::string ratchet::SightCollisionComponent::GetType(void) const {
    return ratchet::CollisionComponentType::kSightCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::SightCollisionComponent::GetSphere(void) {    
    if (_sight_recognition.expired()) {
        return std::optional<Mof::CSphere>();
    } // if
    if (super::GetOwner() ->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto sight = _sight_recognition.lock();
    return Mof::CSphere(super::GetOwner()->GetPosition(), sight->GetRange());
}

std::optional<Mof::CBoxAABB> ratchet::SightCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::SightCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::SightCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<ratchet::SightObject> ratchet::SightCollisionComponent::GetSightObject(void) {
    if (_sight_recognition.expired()) {
        return std::optional<ratchet::SightObject>();
    } // if
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<ratchet::SightObject>();
    } // if
    return ratchet::SightObject(super::GetOwner()->GetPosition(), super::GetOwner()->GetRotate());
}

bool ratchet::SightCollisionComponent::Initialize(void) {
    super::Initialize();
    _sight_recognition = super::GetOwner()->GetComponent<ratchet::SightRecognitionComponent>();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::SightCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::SightCollisionComponent>(*this);
}