#include "EnemyBulletCollisionComponent.h"

#include "CollisionComponentDefine.h"


rachet::EnemyBulletCollisionComponent::EnemyBulletCollisionComponent(int priority) :
    super(priority) {
}

rachet::EnemyBulletCollisionComponent::EnemyBulletCollisionComponent(const EnemyBulletCollisionComponent& obj) :
    super(obj) {
}

rachet::EnemyBulletCollisionComponent::~EnemyBulletCollisionComponent() {
}

std::string rachet::EnemyBulletCollisionComponent::GetType(void) const {
    return rachet::CollisionComponentType::kEnemyBulletCollisionComponent;
}

std::optional<Mof::CSphere> rachet::EnemyBulletCollisionComponent::GetSphere(void) {
    if (super::GetOwner()->GetState() == rachet::ActorState::End) {
        return std::optional<Mof::CSphere>();
    } // if
    return Mof::CSphere(super::GetOwner()->GetPosition(), 0.2f);
}

std::optional<Mof::CBoxAABB> rachet::EnemyBulletCollisionComponent::GetBox(void) {
    return std::optional<Mof::CBoxAABB>();
}

std::optional<Mof::CRay3D> rachet::EnemyBulletCollisionComponent::GetRay(void) {
    return std::optional<Mof::CRay3D>();
}

std::optional<Mof::LPMeshContainer> rachet::EnemyBulletCollisionComponent::GetMesh(void) {
    return std::optional<Mof::LPMeshContainer>();
}

std::optional<rachet::SightObject> rachet::EnemyBulletCollisionComponent::GetSightObject(void) {
    return std::optional<rachet::SightObject>();
}

bool rachet::EnemyBulletCollisionComponent::Initialize(void) {
    super::Initialize();
    return true;
}

std::shared_ptr<rachet::Component> rachet::EnemyBulletCollisionComponent::Clone(void) {
    return std::make_shared<rachet::EnemyBulletCollisionComponent>(*this);
}

void rachet::EnemyBulletCollisionComponent::CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) {
}