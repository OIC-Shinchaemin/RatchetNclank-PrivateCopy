#include "EnemyBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


ratchet::component::collision::EnemyBulletCollisionComponent::EnemyBulletCollisionComponent(int priority) :
    super(priority) {
}

ratchet::component::collision::EnemyBulletCollisionComponent::EnemyBulletCollisionComponent(const EnemyBulletCollisionComponent& obj) :
    super(obj) {
}

ratchet::component::collision::EnemyBulletCollisionComponent::~EnemyBulletCollisionComponent() {
}

std::string ratchet::component::collision::EnemyBulletCollisionComponent::GetType(void) const {
    return ratchet::component::collision::CollisionComponentType::kEnemyBulletCollisionComponent;
}

std::optional<Mof::CSphere> ratchet::component::collision::EnemyBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == ratchet::actor::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    return Mof::CSphere(super::GetOwner()->GetPosition(), 0.2f);
}

std::optional<Mof::CBoxAABB> ratchet::component::collision::EnemyBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> ratchet::component::collision::EnemyBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> ratchet::component::collision::EnemyBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<::ratchet::component::collision::SightObject> ratchet::component::collision::EnemyBulletCollisionComponent::GetSightObject(void) {
    return std::optional<::ratchet::component::collision::SightObject>();
}

bool ratchet::component::collision::EnemyBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::collision::EnemyBulletCollisionComponent::Clone(void) {
    return std::make_shared<ratchet::component::collision::EnemyBulletCollisionComponent>(*this);
}

void ratchet::component::collision::EnemyBulletCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}