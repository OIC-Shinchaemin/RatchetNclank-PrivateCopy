#include "BombGloveEffectCollisionComponent.h"


my::BombGloveEffectCollisionComponent::BombGloveEffectCollisionComponent(int priority) :
    super(priority) {
}

my::BombGloveEffectCollisionComponent::BombGloveEffectCollisionComponent(const BombGloveEffectCollisionComponent& obj) :
    super(obj._priority) {
}

my::BombGloveEffectCollisionComponent::~BombGloveEffectCollisionComponent() {
}

std::string my::BombGloveEffectCollisionComponent::GetType(void) const {
    return "BombGloveEffectCollisionComponent";
}

std::optional<Mof::CSphere> my::BombGloveEffectCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == my::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    //auto scale = 
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> my::BombGloveEffectCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> my::BombGloveEffectCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> my::BombGloveEffectCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<my::SightObject> my::BombGloveEffectCollisionComponent::GetSightObject(void) {
    return std::optional<my::SightObject>();
}

bool my::BombGloveEffectCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<my::Component> my::BombGloveEffectCollisionComponent::Clone(void) {
    return std::make_shared<my::BombGloveEffectCollisionComponent>(*this);
}

void my::BombGloveEffectCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh) {
    if (!this->GetSphere().has_value()) {
        return;
    } // if

    Mof::COLLISIONOUTGEOMETRY info;
    if (this->GetSphere().value().CollisionMesh(mesh, info)) {
        super::GetOwner()->End();
    } // if
}