#include "BombGloveEffectCollisionComponent.h"

#include "CollisionComponentDefine.h"


ratchet::BombGloveEffectCollisionComponent::BombGloveEffectCollisionComponent(int priority) :
    super(priority) {
}

ratchet::BombGloveEffectCollisionComponent::BombGloveEffectCollisionComponent(const BombGloveEffectCollisionComponent& obj) :
    super(obj) {
}

ratchet::BombGloveEffectCollisionComponent::~BombGloveEffectCollisionComponent() {
}

std::string ratchet::BombGloveEffectCollisionComponent::GetType(void) const {
    return ratchet::CollisionComponentType::kBombGloveEffectCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::BombGloveEffectCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    //auto scale = 
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> ratchet::BombGloveEffectCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::BombGloveEffectCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::BombGloveEffectCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<ratchet::SightObject> ratchet::BombGloveEffectCollisionComponent::GetSightObject(void) {
    return std::optional<ratchet::SightObject>();
}

bool ratchet::BombGloveEffectCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::BombGloveEffectCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::BombGloveEffectCollisionComponent>(*this);
}