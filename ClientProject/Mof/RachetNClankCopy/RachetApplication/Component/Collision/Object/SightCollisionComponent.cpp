#include "SightCollisionComponent.h"

#include "../../SightRecognitionComponent.h"


my::SightCollisionComponent::SightCollisionComponent(int priority) :
    super(priority),
    _sight_recognition() {
}

my::SightCollisionComponent::SightCollisionComponent(const SightCollisionComponent& obj) :
    super(obj._priority),
    _sight_recognition() {
}

my::SightCollisionComponent::~SightCollisionComponent() {
}

std::string my::SightCollisionComponent::GetType(void) const {
    return "SightCollisionComponent";
}

std::optional<Mof::CSphere> my::SightCollisionComponent::GetSphere(void) {    
    if (_sight_recognition.expired()) {
        return std::optional<Mof::CSphere>();
    } // if
    if (super::GetOwner() ->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto sight = _sight_recognition.lock();
    return Mof::CSphere(super::GetOwner()->GetPosition(), sight->GetRange());
}

std::optional<Mof::CBoxAABB> my::SightCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::SightCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::SightCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::SightCollisionComponent::GetSightObject(void) {
    if (_sight_recognition.expired()) {
        return std::optional<my::SightObject>();
    } // if
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<my::SightObject>();
    } // if
    return my::SightObject(super::GetOwner()->GetPosition(), super::GetOwner()->GetRotate());
}

bool my::SightCollisionComponent::Initialize(void) {
    super::Initialize();
    _sight_recognition = super::GetOwner()->GetComponent<my::SightRecognitionComponent>();
    return true;
}

std::shared_ptr<my::Component> my::SightCollisionComponent::Clone(void) {
    return std::make_shared<my::SightCollisionComponent>(*this);
}