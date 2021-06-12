#include "BombGloveBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


ratchet::component::collision::BombGloveBulletCollisionComponent::BombGloveBulletCollisionComponent(int priority) :
    super(priority) {
}

ratchet::component::collision::BombGloveBulletCollisionComponent::BombGloveBulletCollisionComponent(const BombGloveBulletCollisionComponent& obj) :
    super(obj) {
}

ratchet::component::collision::BombGloveBulletCollisionComponent::~BombGloveBulletCollisionComponent() {
}

std::string ratchet::component::collision::BombGloveBulletCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kBombGloveBulletCollisionComponent;
    //return "BombGloveBulletCollisionComponent";
}

std::optional<Mof::CSphere> ratchet::component::collision::BombGloveBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, 0.2f);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::BombGloveBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::BombGloveBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::BombGloveBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::BombGloveBulletCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::BombGloveBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::BombGloveBulletCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::BombGloveBulletCollisionComponent>(*this);
}

void ratchet::component::collision::BombGloveBulletCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
    if (!this->GetSphere().has_value()) {
        return;
    } // if

    Mof::COLLISIONOUTGEOMETRY info;
    if (this->GetSphere().value().CollisionMesh(mesh, info)) {
        super::GetOwner()->End();
    } // if
}