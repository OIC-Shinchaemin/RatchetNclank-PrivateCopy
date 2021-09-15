#include "BombGloveEffectCollisionComponent.h"

#include "../CollisionComponentDefine.h"


ratchet::component::collision::BombGloveEffectCollisionComponent::BombGloveEffectCollisionComponent(int priority) :
    super(priority) {
}

ratchet::component::collision::BombGloveEffectCollisionComponent::BombGloveEffectCollisionComponent(const BombGloveEffectCollisionComponent& obj) :
    super(obj) {
}

ratchet::component::collision::BombGloveEffectCollisionComponent::~BombGloveEffectCollisionComponent() {
}

std::string ratchet::component::collision::BombGloveEffectCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBombGloveEffectCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::BombGloveEffectCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    //auto scale = 
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::BombGloveEffectCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::BombGloveEffectCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::BombGloveEffectCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::BombGloveEffectCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::BombGloveEffectCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::BombGloveEffectCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::BombGloveEffectCollisionComponent>(*this);
}