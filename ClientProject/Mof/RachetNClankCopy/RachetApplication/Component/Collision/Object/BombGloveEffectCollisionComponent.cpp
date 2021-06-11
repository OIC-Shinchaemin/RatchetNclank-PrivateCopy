#include "BombGloveEffectCollisionComponent.h"

#include "CollisionComponentDefine.h"


rachet::BombGloveEffectCollisionComponent::BombGloveEffectCollisionComponent(int priority) :
    super(priority) {
}

rachet::BombGloveEffectCollisionComponent::BombGloveEffectCollisionComponent(const BombGloveEffectCollisionComponent& obj) :
    super(obj) {
}

rachet::BombGloveEffectCollisionComponent::~BombGloveEffectCollisionComponent() {
}

std::string rachet::BombGloveEffectCollisionComponent::GetType(void) const {
    return rachet::CollisionComponentType::kBombGloveEffectCollisionComponent;
}

std::optional<Mof::CSphere> rachet::BombGloveEffectCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == rachet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    //auto scale = 
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> rachet::BombGloveEffectCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> rachet::BombGloveEffectCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> rachet::BombGloveEffectCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<rachet::SightObject> rachet::BombGloveEffectCollisionComponent::GetSightObject(void) {
    return std::optional<rachet::SightObject>();
}

bool rachet::BombGloveEffectCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<rachet::Component> rachet::BombGloveEffectCollisionComponent::Clone(void) {
    return std::make_shared<rachet::BombGloveEffectCollisionComponent>(*this);
}