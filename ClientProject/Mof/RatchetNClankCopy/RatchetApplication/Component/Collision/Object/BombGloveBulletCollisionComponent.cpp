#include "BombGloveBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


ratchet::BombGloveBulletCollisionComponent::BombGloveBulletCollisionComponent(int priority) :
    super(priority) {
}

ratchet::BombGloveBulletCollisionComponent::BombGloveBulletCollisionComponent(const BombGloveBulletCollisionComponent& obj) :
    super(obj) {
}

ratchet::BombGloveBulletCollisionComponent::~BombGloveBulletCollisionComponent() {
}

std::string ratchet::BombGloveBulletCollisionComponent::GetType(void) const {
    return ratchet::CollisionComponentType::kBombGloveBulletCollisionComponent;
    //return "BombGloveBulletCollisionComponent";
}

std::optional<Mof::CSphere> ratchet::BombGloveBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> ratchet::BombGloveBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::BombGloveBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::BombGloveBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<ratchet::SightObject> ratchet::BombGloveBulletCollisionComponent::GetSightObject(void) {
    return std::optional<ratchet::SightObject>();
}

bool ratchet::BombGloveBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::BombGloveBulletCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::BombGloveBulletCollisionComponent>(*this);
}

void ratchet::BombGloveBulletCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
    if (!this->GetSphere().has_value()) {
        return;
    } // if

    Mof::COLLISIONOUTGEOMETRY info;
    if (this->GetSphere().value().CollisionMesh(mesh, info)) {
        super::GetOwner()->End();
    } // if
}