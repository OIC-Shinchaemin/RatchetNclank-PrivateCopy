#include "EnemySightCollisionComponent.h"

#include "../../SightRecognitionComponent.h"


my::EnemySightCollisionComponent::EnemySightCollisionComponent(int priority) :
    super(priority),
    _sight_recognition() {
}

my::EnemySightCollisionComponent::EnemySightCollisionComponent(const EnemySightCollisionComponent& obj) :
    super(obj._priority),
    _sight_recognition() {
}

my::EnemySightCollisionComponent::~EnemySightCollisionComponent() {
}

std::string my::EnemySightCollisionComponent::GetType(void) const {
    return "EnemySightCollisionComponent";
}

std::optional<Mof::CSphere> my::EnemySightCollisionComponent::GetSphere(void) {    
    if (_sight_recognition.expired()) {
        return std::optional<Mof::CSphere>();
    } // if
    if (super::GetOwner() ->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto sight = _sight_recognition.lock();
    return Mof::CSphere(super::GetOwner()->GetPosition(), sight->GetRange());
}

std::optional<Mof::CBoxAABB> my::EnemySightCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::EnemySightCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::EnemySightCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::EnemySightCollisionComponent::GetSightObject(void) {
    if (_sight_recognition.expired()) {
        return std::optional<my::SightObject>();
    } // if
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<my::SightObject>();
    } // if
    return my::SightObject(super::GetOwner()->GetPosition(), super::GetOwner()->GetRotate());
}

bool my::EnemySightCollisionComponent::Initialize(void) {
    super::Initialize();
    _sight_recognition = super::GetOwner()->GetComponent<my::SightRecognitionComponent>();
    return true;
}

std::shared_ptr<my::Component> my::EnemySightCollisionComponent::Clone(void) {
    return std::make_shared<my::EnemySightCollisionComponent>(*this);
}