#include "SightCollisionComponent.h"

#include "CollisionComponentDefine.h"
#include "../../SightRecognitionComponent.h"


rachet::SightCollisionComponent::SightCollisionComponent(int priority) :
    super(priority),
    _sight_recognition() {
}

rachet::SightCollisionComponent::SightCollisionComponent(const SightCollisionComponent& obj) :
    super(obj),
    _sight_recognition() {
}

rachet::SightCollisionComponent::~SightCollisionComponent() {
}

std::string rachet::SightCollisionComponent::GetType(void) const {
    return rachet::CollisionComponentType::kSightCollisionComponent;
}

std::optional<Mof::CSphere> rachet::SightCollisionComponent::GetSphere(void) {    
    if (_sight_recognition.expired()) {
        return std::optional<Mof::CSphere>();
    } // if
    if (super::GetOwner() ->GetState() == rachet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto sight = _sight_recognition.lock();
    return Mof::CSphere(super::GetOwner()->GetPosition(), sight->GetRange());
}

std::optional<Mof::CBoxAABB> rachet::SightCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> rachet::SightCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> rachet::SightCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<rachet::SightObject> rachet::SightCollisionComponent::GetSightObject(void) {
    if (_sight_recognition.expired()) {
        return std::optional<rachet::SightObject>();
    } // if
    if (super::GetOwner()->GetState() == rachet::ActorState::End) {
        return std::optional<rachet::SightObject>();
    } // if
    return rachet::SightObject(super::GetOwner()->GetPosition(), super::GetOwner()->GetRotate());
}

bool rachet::SightCollisionComponent::Initialize(void) {
    super::Initialize();
    _sight_recognition = super::GetOwner()->GetComponent<rachet::SightRecognitionComponent>();
    return true;
}

std::shared_ptr<rachet::Component> rachet::SightCollisionComponent::Clone(void) {
    return std::make_shared<rachet::SightCollisionComponent>(*this);
}