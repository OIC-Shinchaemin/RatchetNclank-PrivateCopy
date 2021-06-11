#include "EnemyBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


ratchet::EnemyBulletCollisionComponent::EnemyBulletCollisionComponent(int priority) :
    super(priority) {
}

ratchet::EnemyBulletCollisionComponent::EnemyBulletCollisionComponent(const EnemyBulletCollisionComponent& obj) :
    super(obj) {
}

ratchet::EnemyBulletCollisionComponent::~EnemyBulletCollisionComponent() {
}

std::string ratchet::EnemyBulletCollisionComponent::GetType(void) const {
    return ratchet::CollisionComponentType::kEnemyBulletCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::EnemyBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    return Mof::CSphere(super::GetOwner()->GetPosition(), 0.2f);
}

std::optional<Mof::CBoxAABB> ratchet::EnemyBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::EnemyBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::EnemyBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<ratchet::SightObject> ratchet::EnemyBulletCollisionComponent::GetSightObject(void) {
    return std::optional<ratchet::SightObject>();
}

bool ratchet::EnemyBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::EnemyBulletCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::EnemyBulletCollisionComponent>(*this);
}

void ratchet::EnemyBulletCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}